#include "tree.h"

int main()
{
	NodeDecision * decisionTree = nullptr;
	readDecisionInput(decisionTree);

	NodeOutput * outputTree = nullptr;
	readAttributesInput(decisionTree, outputTree);

	writeToFile(outputTree);

	clear(decisionTree);
	clear(outputTree);

	cout << "Zapisano do pliku Output.txt" << endl;

	cin.get();
	cin.get();
	return 0;
}