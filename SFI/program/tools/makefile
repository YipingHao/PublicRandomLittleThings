BASE = ../


ODIR = $(BASE)obj/
CODE = $(BASE)code/
TOOLS = $(BASE)tools/
TEST = $(BASE)test/

COFILE = $(ODIR)sheet.o $(ODIR)analyzer.o $(ODIR)SFI.o $(ODIR)xyz.o $(ODIR)automata.o $(ODIR)dictionary.o $(ODIR)analyzerthread.o $(ODIR)printer.o $(ODIR)parser.o $(ODIR)template.o $(ODIR)SFI_v02_core.o $(ODIR)SFI_v02_element_data.o $(ODIR)SFI_v02_task.o

TestOFile = $(TEST)test.o $(TEST)test_sfi_v02.o $(TEST)main.o
HFILES = $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h

OPTION ?= -O2
#OPTION = -O3
#EXTRA # =-Wall -Wextra -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations -Wconversion -ftrapv
#CC = icc
CC = g++
CFLAGS = $(OPTION) $(EXTRA)
CXX11FLAGS = $(CFLAGS) -std=c++11 -pthread



#TestOFile = $(TEST)main.o $(ODIR)lexical.o



libFIanalyzer.a:  $(COFILE)
	ar -rcv $(BASE)libFIanalyzer.a  $(COFILE)

#$(ODIR)lexical.o:$(CODE)lexical.cpp $(CODE)lexical.h
#	g++ -o $(ODIR)lexical.o -c -O3  $(CODE)lexical.cpp

$(ODIR)sheet.o:$(CODE)sheet.cpp $(CODE)sheet.h
	$(CC) -o $(ODIR)sheet.o -c $(CFLAGS) $(CODE)sheet.cpp 

# Add template.cpp compilation
$(ODIR)template.o:$(CODE)template.cpp $(CODE)template.h
	$(CC) -o $(ODIR)template.o -c $(CFLAGS) $(CODE)template.cpp 

$(ODIR)analyzer.o:$(CODE)analyzer.cpp $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h
	$(CC) -o $(ODIR)analyzer.o -c $(CFLAGS) $(CODE)analyzer.cpp 

$(ODIR)SFI.o:$(CODE)SFI.cpp $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h
	$(CC) -o $(ODIR)SFI.o -c $(CFLAGS) $(CODE)SFI.cpp

$(ODIR)SFI_v02_core.o:$(CODE)SFI_v02/sfi_v02.cpp $(CODE)SFI_v02/sfi_v02.h $(CODE)analyzer.h
	$(CC) -o $(ODIR)SFI_v02_core.o -c $(CXX11FLAGS) $(CODE)SFI_v02/sfi_v02.cpp

$(ODIR)SFI_v02_element_data.o:$(CODE)SFI_v02/element_data.cpp $(CODE)SFI_v02/element_data.h
	$(CC) -o $(ODIR)SFI_v02_element_data.o -c $(CXX11FLAGS) $(CODE)SFI_v02/element_data.cpp

$(ODIR)SFI_v02_task.o:$(CODE)SFI_v02/task.cpp $(CODE)SFI_v02/task.h $(CODE)SFI_v02/sfi_v02.h $(CODE)SFI_v02/element_data.h $(CODE)dictionary.h
	$(CC) -o $(ODIR)SFI_v02_task.o -c $(CXX11FLAGS) $(CODE)SFI_v02/task.cpp

$(ODIR)xyz.o:$(CODE)xyz.cpp $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h
	$(CC) -o $(ODIR)xyz.o -c $(CFLAGS) $(CODE)xyz.cpp

$(ODIR)analyzerthread.o:$(CODE)analyzerthread.cpp $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h
	$(CC) -o $(ODIR)analyzerthread.o -c $(CFLAGS) $(CODE)analyzerthread.cpp 

$(ODIR)printer.o:$(CODE)printer.cpp $(HFILES)
	$(CC) -o $(ODIR)printer.o -c $(CFLAGS) $(CODE)printer.cpp 

$(ODIR)parser.o:$(CODE)parser.cpp $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h
	$(CC) -o $(ODIR)parser.o -c $(CFLAGS) $(CODE)parser.cpp 

$(ODIR)automata.o:$(CODE)automata.cpp $(CODE)automata.h
	$(CC) -o $(ODIR)automata.o -c $(CFLAGS) $(CODE)automata.cpp 

$(ODIR)dictionary.o:$(CODE)dictionary.cpp $(CODE)dictionary.h $(CODE)automata.h 
	$(CC) -o $(ODIR)dictionary.o -c $(CFLAGS) $(CODE)dictionary.cpp 

test.exe: $(COFILE) $(TestOFile) 
	$(CC) -o $(TEST)test.exe $(COFILE) $(TestOFile) -pthread

$(TEST)test.o: $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h $(TEST)test.cpp
	$(CC) -o $(TEST)test.o -c $(CFLAGS) $(TEST)test.cpp

$(TEST)test_sfi_v02.o: $(TEST)test_sfi_v02.cpp $(CODE)SFI_v02/sfi_v02.h $(CODE)SFI_v02/element_data.h $(CODE)analyzer.h
	$(CC) -o $(TEST)test_sfi_v02.o -c $(CXX11FLAGS) $(TEST)test_sfi_v02.cpp

$(TEST)main.o: $(TEST)main.cpp $(CODE)analyzer.h $(CODE)sheet.h $(CODE)automata.h $(CODE)dictionary.h $(CODE)template.h $(CODE)SFI_v02/task.h $(CODE)SFI_v02/sfi_v02.h
	$(CC) -o $(TEST)main.o -c $(CXX11FLAGS) $(TEST)main.cpp

benchmark-sfi-v02.exe: $(COFILE) $(TEST)benchmark_sfi_v02.o
	$(CC) -o $(TEST)benchmark-sfi-v02.exe $(COFILE) $(TEST)benchmark_sfi_v02.o -pthread

$(TEST)benchmark_sfi_v02.o: $(TEST)benchmark_sfi_v02.cpp $(CODE)SFI_v02/sfi_v02.h $(CODE)analyzer.h
	$(CC) -o $(TEST)benchmark_sfi_v02.o -c $(CXX11FLAGS) $(TEST)benchmark_sfi_v02.cpp

#$(ODIR)FIanalyzer.o:$(CODE)FIanalyzer.cpp $(CODE)FIanalyzer.h
#	$(CC) -o $(ODIR)FIanalyzer.o -c -std=c++11 -O3  $(CODE)FIanalyzer.cpp

#$(ODIR)xyz.o:$(CODE)xyz.cpp $(CODE)FIanalyzer.h
#	g++ -o $(ODIR)xyz.o -c -std=c++11 -O3  $(CODE)xyz.cpp

#LIBlex = -L $(BASE)extern/lib -lHyperAcc
#libHyperAcc.h

#test.exe: $(COFILE) $(TestOFile)
#	g++ -o $(TEST)test.exe $(COFILE) $(TestOFile)

#test.exe: $(COFILE) $(TestOFile) $(CODE)libHyperAcc.h
#	g++ -o $(TEST)test.exe $(COFILE) $(TEST)main.o $(LIBlex) -lpthread

#$(TEST)main.o: $(CODE)FIanalyzer.h $(TEST)main.cpp $(CODE)lexical.h
#	g++ -o $(TEST)main.o -c -O3 $(TEST)main.cpp

#$(TEST)main.o: $(CODE)FIanalyzer.h $(TEST)main.cpp
#	g++ -o $(TEST)main.o -c -O3 $(TEST)main.cpp


.PHONY: clean
clean:
	rm $(ODIR)*.o
	rm $(TEST)*.o





