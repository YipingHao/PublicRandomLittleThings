"""Recover readable Markdown from HTML exported by VS Code Markdown Preview.

The converter intentionally prefers KaTeX's embedded ``application/x-tex``
annotations, which retain the original LaTeX better than copying visible math.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

from lxml import html


def classes(node) -> set[str]:
    return set((node.get("class") or "").split())


def tex_annotation(node) -> str | None:
    values = node.xpath('.//annotation[@encoding="application/x-tex"]/text()')
    if not values:
        return None
    return values[0].strip()


def inline(node) -> str:
    tag = node.tag.lower() if isinstance(node.tag, str) else ""

    if "katex" in classes(node):
        tex = tex_annotation(node)
        return f"${tex}$" if tex else ""
    if tag in {"script", "style"}:
        return ""
    if tag == "br":
        return "  \n"

    prefix = node.text or ""
    pieces = [prefix]
    for child in node:
        pieces.append(inline(child))
        pieces.append(child.tail or "")
    content = "".join(pieces)

    if tag in {"strong", "b"}:
        return f"**{content}**"
    if tag in {"em", "i"}:
        return f"*{content}*"
    if tag == "code":
        ticks = "``" if "`" in content else "`"
        return f"{ticks}{content}{ticks}"
    if tag == "a":
        href = node.get("href") or ""
        return f"[{content}]({href})" if href else content
    if tag == "img":
        return f"![{node.get('alt') or ''}]({node.get('src') or ''})"

    return content


def list_block(node, ordered: bool, depth: int = 0) -> str:
    lines: list[str] = []
    items = [child for child in node if isinstance(child.tag, str) and child.tag.lower() == "li"]
    for index, item in enumerate(items, start=1):
        marker = f"{index}." if ordered else "-"
        nested = [
            child
            for child in item
            if isinstance(child.tag, str) and child.tag.lower() in {"ul", "ol"}
        ]
        text_parts = [item.text or ""]
        for child in item:
            if child in nested:
                continue
            text_parts.extend([inline(child), child.tail or ""])
        text = re.sub(r"\s+", " ", "".join(text_parts)).strip()
        lines.append(f"{'    ' * depth}{marker} {text}")
        for child in nested:
            lines.append(list_block(child, child.tag.lower() == "ol", depth + 1).rstrip())
    return "\n".join(lines) + "\n"


def block(node) -> str:
    tag = node.tag.lower() if isinstance(node.tag, str) else ""

    if tag in {"script", "style"}:
        return ""
    if tag in {"h1", "h2", "h3", "h4", "h5", "h6"}:
        return f"{'#' * int(tag[1])} {inline(node).strip()}\n"
    if tag == "p" and "katex-block" in classes(node):
        tex = tex_annotation(node)
        return f"$$\n{tex}\n$$\n" if tex else ""
    if tag == "p":
        return inline(node).strip() + "\n"
    if tag == "pre":
        code = "".join(node.itertext()).rstrip()
        language = ""
        code_nodes = node.xpath("./code")
        if code_nodes:
            language_class = next(
                (value for value in classes(code_nodes[0]) if value.startswith("language-")),
                "",
            )
            language = language_class.removeprefix("language-")
        return f"```{language}\n{code}\n```\n"
    if tag in {"ul", "ol"}:
        return list_block(node, tag == "ol")
    if tag == "blockquote":
        content = "\n\n".join(block(child).strip() for child in node if block(child).strip())
        return "\n".join(f"> {line}" for line in content.splitlines()) + "\n"
    if tag == "hr":
        return "---\n"
    return inline(node).strip() + "\n"


def convert(source: Path) -> str:
    document = html.parse(str(source))
    bodies = document.xpath("//body")
    if not bodies:
        raise ValueError(f"No <body> element found in {source}")

    chunks = [block(child).strip() for child in bodies[0] if block(child).strip()]
    markdown = "\n\n".join(chunks).strip() + "\n"
    markdown = re.sub(r"[ \t]+\n", "\n", markdown)
    return markdown


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path, help="VS Code-exported HTML file")
    parser.add_argument("output", type=Path, help="Markdown file to create")
    args = parser.parse_args()

    if args.output.exists():
        raise FileExistsError(f"Refusing to overwrite existing file: {args.output}")

    markdown = convert(args.source)
    args.output.write_text(markdown, encoding="utf-8", newline="\n")
    print(f"Recovered {len(markdown)} characters to {args.output}")


if __name__ == "__main__":
    main()

