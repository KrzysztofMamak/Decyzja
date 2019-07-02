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
 *	W�ze� drzewa wyj�ciowego
 */
struct NodeOutput
{
	string name;
	vector<vector<double>> values;
	NodeOutput * left;
	NodeOutput * right;
};

/**
 *	W�ze� drzewa decyzyjnego
 */
struct NodeDecision
{
	Decision decision;
	NodeDecision * left;
	NodeDecision * right;
};

/**
 *	Funkcja dodaje element do drzewa decyzyjnego.
 *	@param rootDecision korze� drzewa decyzyjnego
 *	@param decision dodawany element
 */
void add(NodeDecision * & rootDecision, const Decision & decision);

/**
 *	Funkcja znajduje przysz�ego ojca dla elementu o podanym indeksie w�z�a.
 *	@param rootDecision korze� w�z�a decyzyjnego
 *	@param newNode wska�nik do znalezionego w�z�a
 *	@param index indeks elementu, dla kt�rego funkcja znajduje ojca
 */
void find(NodeDecision * & rootDecision, NodeDecision * & newNode, const int & index);

/**
 *	Funkcja usuwa drzewo z pami�ci.
 *	@param rootDecision korze� drzewa do usuni�cia
 */
void clear(NodeDecision * & rootDecision);

/**
 *	Funkcja wczytuje plik z opisem drzewa decyzyjnego i zapisuje dane w drzewie.
 *	@param rootDecision korze� drzewa decyzyjnego
 */
void readDecisionInput(NodeDecision * & rootDecision);

/**
 *	Funkcja wczytuje plik z warto�ciami atrybut�w i umieszcza dane w drzewie wyj�ciowym.
 *	@param rootDecision korze� drzewa decyzyjnego
 *	@param rootOutput korze� drzewa wyj�ciowego
 */
void readAttributesInput(NodeDecision * & rootDecision, NodeOutput * & rootOutput);

/**
 *	Funkcja pomocnicza, kt�ra dobiera kategori� do podanego
 *	zestawu warto�ci i zapisuje dane w drzewie wyj�ciowym.
 *	@param rootDecision korze� drzewa decyzyjnego
 *	@param rootOutput korze� drzewa wyj�ciowego
 *	@param attributes nazwy atrybut�w
 *	@param values warto�ci atrybut�w
 */
void add(NodeDecision * & rootDecision, NodeOutput * & rootOutput,
	const vector<string> & attributes, const vector<double> & values);

/**
 *	Funkcja dodaje element do drzewa wyj�ciowego.
 *	@param rootOutput korze� drzewa wyj�ciowego
 *	@param attribute nazwa atrybutu
 *	@param values warto�ci atrybut�w
 */
void add(NodeOutput * & rootOutput, const string & attribute,
	const vector<double> & values);

/**
 *	Funkcja zwraca nazw� kategorii dla podanego zestawu warto�ci atrybut�w.
 *	@param rootDecision korze� drzewa decyzyjnego
 *	@param attributes nazwy atrybut�w
 *	@param values warto�ci atrybut�w
 */
string match(NodeDecision * & rootDecision, const vector<string> & attributes,
	const vector<double> & values);

/**
 *	Funkcja pomocnicza, kt�ra tworzy zmienn� fstream i wywo�uje funkcj� write().
 *	@param rootOutput korze� drzewa wyj�ciowego
 */
void writeToFile(NodeOutput * & rootOutput);

/**
 *	Funkcja zapisuje do pliku dane z drzewa wyj�ciowego.
 *	@param rootOutput korze� drzewa wyj�ciowego
 *	@param file plik, w kt�rym zapisane zostan� dane
 */
void write(NodeOutput * & rootOutput, fstream & file);

/**
 *	Funkcja usuwa drzewo z pami�ci.
 *	@param rootOutput korze� drzewa do usuni�cia
 */
void clear(NodeOutput * & rootOutput);

/**
 *	Funkcja zwraca indeks elementu, kt�ry jest r�wny co do warto�ci podanemu argumentowi.
 *	@param vector nazwy atrybut�w
 *	@param arg �a�cuch znak�w kt�ry nale�y znale�� w wektorze
 *	@return indeks elementu tablicy, maj�cego tak� sam� warto�� jak podany argument
 */
int findPosition(const vector<string> & vector, const string & arg);

#endif 