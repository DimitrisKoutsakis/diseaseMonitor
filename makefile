diseaseMonitor: AVL_Tree.o Hash_Table.o Max_Heap.o PatientList.o PatientRecord.o diseaseMonitor.o
	g++ -std=c++11 *.o -o diseaseMonitor

diseaseMonitor.o: SourceFiles/diseaseMonitor.cpp Hash_Table.o
	g++ -std=c++11 -c SourceFiles/diseaseMonitor.cpp

Hash_Table.o: SourceFiles/Hash_Table.cpp AVL_Tree.o Max_Heap.o
	g++ -std=c++11 -c SourceFiles/Hash_Table.cpp

Max_Heap.o: SourceFiles/Max_Heap.cpp
	g++ -std=c++11 -c SourceFiles/Max_Heap.cpp

AVL_Tree.o: SourceFiles/AVL_Tree.cpp PatientList.o
	g++ -std=c++11 -c SourceFiles/AVL_Tree.cpp

PatientList.o: SourceFiles/PatientList.cpp PatientRecord.o
	g++ -std=c++11 -c SourceFiles/PatientList.cpp

PatientRecord.o: SourceFiles/PatientRecord.cpp
	g++ -std=c++11 -c SourceFiles/PatientRecord.cpp

# diseaseMonitor:
# 	g++ -std=c++11 SourceFiles/*.cpp -o diseaseMonitor

clean:
	rm -f diseaseMonitor *.o