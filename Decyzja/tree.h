#ifndef TREE_H_
/** @file */

#define TREE_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using std::endl;
using std::string;
using std::vector;
using std::fstream;
using std::ios;
using std::istringstream;
using std::cin;
using std::cout;

/**
 *	Warunek w instrukcji dla drzewa decyzyjnego
 */
struct Condition
{
	string attribute;
	double value;
};

/**
 *	Instrukcja dla drzewa decyzyjnego
 */
struct Decision
{
	int indexIn;
	Condition condition;
	string indexOutYes;
	string indexOutNo;
	bool hasLeftChild;
	bool hasRightChild;
};

/**
 *	Wêze³ drzewa wyjœciowego
 */
struct NodeOutput
{
	string name;
	vector<vector<double>> values;
	NodeOutput * left;
	NodeOutput * right;
};

/**
 *	Wêze³ drzewa decyzyjnego
 */
struct NodeDecision
{
	Decision decision;
	NodeDecision * left;
	NodeDecision * right;
};

/**
 *	Funkcja dodaje element do drzewa decyzyjnego.
 *	@param rootDecision korzeñ drzewa decyzyjnego
 *	@param decision dodawany element
 */
void add(NodeDecision * & rootDecision, const Decision & decision);

/**
 *	Funkcja znajduje przysz³ego ojca dla elementu o podanym indeksie wêz³a.
 *	@param rootDecision korzeñ wêz³a decyzyjnego
 *	@param newNode wskaŸnik do znalezionego wêz³a
 *	@param index indeks elementu, dla którego funkcja znajduje ojca
 */
void find(NodeDecision * & rootDecision, NodeDecision * & newNode, const int & index);

/**
 *	Funkcja usuwa drzewo z pamiêci.
 *	@param rootDecision korzeñ drzewa do usuniêcia
 */
void clear(NodeDecision * & rootDecision);

/**
 *	Funkcja wczytuje plik z opisem drzewa decyzyjnego i zapisuje dane w drzewie.
 *	@param rootDecision korzeñ drzewa decyzyjnego
 */
void readDecisionInput(NodeDecision * & rootDecision);

/**
 *	Funkcja wczytuje plik z wartoœciami atrybutów i umieszcza dane w drzewie wyjœciowym.
 *	@param rootDecision korzeñ drzewa decyzyjnego
 *	@param rootOutput korzeñ drzewa wyjœciowego
 */
void readAttributesInput(NodeDecision * & rootDecision, NodeOutput * & rootOutput);

/**
 *	Funkcja pomocnicza, która dobiera kategoriê do podanego
 *	zestawu wartoœci i zapisuje dane w drzewie wyjœciowym.
 *	@param rootDecision korzeñ drzewa decyzyjnego
 *	@param rootOutput korzeñ drzewa wyjœciowego
 *	@param attributes nazwy atrybutów
 *	@param values wartoœci atrybutów
 */
void add(NodeDecision * & rootDecision, NodeOutput * & rootOutput,
	const vector<string> & attributes, const vector<double> & values);

/**
 *	Funkcja dodaje element do drzewa wyjœciowego.
 *	@param rootOutput korzeñ drzewa wyjœciowego
 *	@param attribute nazwa atrybutu
 *	@param values wartoœci atrybutów
 */
void add(NodeOutput * & rootOutput, const string & attribute,
	const vector<double> & values);

/**
 *	Funkcja zwraca nazwê kategorii dla podanego zestawu wartoœci atrybutów.
 *	@param rootDecision korzeñ drzewa decyzyjnego
 *	@param attributes nazwy atrybutów
 *	@param values wartoœci atrybutów
 */
string match(NodeDecision * & rootDecision, const vector<string> & attributes,
	const vector<double> & values);

/**
 *	Funkcja pomocnicza, która tworzy zmienn¹ fstream i wywo³uje funkcjê write().
 *	@param rootOutput korzeñ drzewa wyjœciowego
 */
void writeToFile(NodeOutput * & rootOutput);

/**
 *	Funkcja zapisuje do pliku dane z drzewa wyjœciowego.
 *	@param rootOutput korzeñ drzewa wyjœciowego
 *	@param file plik, w którym zapisane zostan¹ dane
 */
void write(NodeOutput * & rootOutput, fstream & file);

/**
 *	Funkcja usuwa drzewo z pamiêci.
 *	@param rootOutput korzeñ drzewa do usuniêcia
 */
void clear(NodeOutput * & rootOutput);

/**
 *	Funkcja zwraca indeks elementu, który jest równy co do wartoœci podanemu argumentowi.
 *	@param vector nazwy atrybutów
 *	@param arg ³añcuch znaków który nale¿y znaleŸæ w wektorze
 *	@return indeks elementu tablicy, maj¹cego tak¹ sam¹ wartoœæ jak podany argument
 */
int findPosition(const vector<string> & vector, const string & arg);

#endif 