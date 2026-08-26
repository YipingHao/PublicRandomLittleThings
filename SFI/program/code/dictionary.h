#ifndef __DICtionary_hkadgshrgaioasrfhioefashioaefwshio
#define __DICtionary_hkadgshrgaioasrfhioefashioaefwshio
#include "automata.h"
namespace hyperlex
{
    class dictionary
    {
    public:
        enum Ktype
        {
            null_ = 0,
            int_ = 1,
            float_ = 2,
            string_ = 3,
            bool_ = 4,
            dictionary_ = 5,
        };
        union element
        {
            long int ii;
            double ff;
            char* ss;
            bool bb;
            dictionary* dd;
        };
        struct KV
        {
            char* key;
            Ktype T;
            element* Content;
            size_t Capacity;
            size_t Count;
        public:
            KV();
            ~KV();
            void ruin(void);
            void copy(const KV& src);
            void clear(void);
            void initial(void);
            void recapacity(size_t NewSize);
            void append(const element& e);
            void setType(Ktype newType);
            void setName(const char* newKey);

            size_t capacity() const;
            size_t count() const;
            element& operator[](size_t i);
            element const& operator[](size_t i) const;
        };
        enum errorType
        {
            NoError = 0,
            ErrorinputLEXICAL,
            ErrorinputGrammar,
            buildUndone,
        };


        dictionary();
        ~dictionary();
        void print(FILE* fp) const;
        void ErrorDemo(FILE* fp) const;
        int build(FILE* fp);
        int build(const char* input);
        void move(dictionary* source);
        void clear(void);

        element search(Ktype& T, const char* key) const;
        element*search(size_t&count, Ktype& T, const char* key) const;

        const char* search(const char* Default_, const char* key) const;
        bool search(bool Default_, const char* key) const;
        long int search(long int Default_, const char* key) const;
        double search(double Default_, const char* key) const;

        //bool search(dictionary *out, const char* key) const;
        //返回值数量，out指向第一个元素，如果没有就返回0，out指向nullptr
        //进入函数后，会free掉原来out指向的内存（如果不为nullptr），并重新分配内存存储结果
        //可以套壳element*search(size_t&count, Ktype& T, const char* key) const;
        size_t search(double*& out, const char* key) const;
        size_t search(long int*& out, const char* key) const;
        size_t search(char**& out, const char* key) const;


        size_t append(const char* key, element value, Ktype T);
        size_t append(const char* key, const char* value);
        size_t append(const char* key, double value);
        size_t append(const char* key, long int value);
        size_t append(const char* key, int value);
        size_t append(const char* key, size_t value);
        size_t append(const char* key, bool value);
        size_t append(const char* key, dictionary* value);

        size_t assign(const char* key, element value, Ktype T);
        size_t assign(const char* key, const char* value);
        void copy(const dictionary& source);
    private:
        typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor> GLTree;
        typedef hyperlex::tree<hyperlex::GrammarTree::TreeInfor>::PostIterator GTIter;
        hyperlex::vector<KV> Content;

        Morpheme LexicalSource;

        errorType errorCode;
        size_t errorInfor1;
        size_t errorInfor2;

        void move(KV*& source);

        void print(FILE* fp, size_t indent) const;  // �ݹ��ӡ����
        void PrintTab(FILE* fp, size_t count) const; // �������ߺ���

        // ����ר�ô�ӡ����
        //void PrintValue(FILE* fp, const element& e, Ktype T, size_t indent) const;
        void PrintArray(FILE* fp, const KV& kv, size_t indent) const;
        void NeglectNullToken(hyperlex::Morpheme& eme) const;
        int buildGanalysis(const hyperlex::Morpheme& eme);
        int buildAll(const hyperlex::Morpheme& eme, hyperlex::GrammarTree& Tree);
        element buildUnit(Ktype& T, const hyperlex::Morpheme& eme, GLTree* GT);
    };

}


#endif
