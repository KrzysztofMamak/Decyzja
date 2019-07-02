#include "tree.h"

void add(NodeDecision * & rootDecision, const Decision & decision)
{
	if (!rootDecision)
		rootDecision = new NodeDecision{ decision, nullptr, nullptr };
	else
	{
		NodeDecision * newNode = nullptr;
		find(rootDecision, newNode, decision.indexIn);

		if (decision.indexIn == atoi(newNode->decision.indexOutNo.c_str()))
			newNode->left = new NodeDecision{ decision, nullptr, nullptr };
		else
			newNode->right = new NodeDecision{ decision, nullptr, nullptr };
	}
}

void find(NodeDecision * & rootDecision, NodeDecision * & newNode, const int & index)
{
	if (atoi(rootDecision->decision.indexOutNo.c_str()) == index
		|| atoi(rootDecision->decision.indexOutYes.c_str()) == index)
	{
		newNode = rootDecision;
		return;
	}
	else
	{
		if (rootDecision->left != nullptr)
			find(rootDecision->left, newNode, index);
		if (rootDecision->right != nullptr)
			find(rootDecision->right, newNode, index);
	}
}

void clear(NodeDecision * & rootDecision)
{
	if (rootDecision)
	{
		clear(rootDecision->left);
		clear(rootDecision->right);

		delete rootDecision;
		rootDecision = nullptr;
	}
}

void readDecisionInput(NodeDecision * & rootDecision)
{
	fstream file("TreeDescription.txt", ios::in);
	if (file.is_open())
	{
		while (!file.eof())
		{
			Decision decision;
			file >> decision.indexIn;
			file >> decision.condition.attribute;
			file >> decision.condition.value;
			file >> decision.indexOutNo;
			file >> decision.indexOutYes;
			if (isdigit(decision.indexOutYes[0]))
				decision.hasRightChild = true;
			else
				decision.hasRightChild = false;
			if (isdigit(decision.indexOutNo[0]))
				decision.hasLeftChild = true;
			else
				decision.hasLeftChild = false;
			add(rootDecision, decision);
		}
	}
}

void readAttributesInput(NodeDecision * & rootDecision, NodeOutput * & rootOutput)
{
	fstream file("Records.txt", ios::in);
	if (file.is_open())
	{
		vector<string> attributes;
		string attributesString;
		string attribute;
		getline(file, attributesString);
		istringstream iss(attributesString);

		while (iss >> attribute)
			attributes.push_back(attribute);

		while (!file.eof())
		{
			double value;
			string line;
			vector<double> values;
			getline(file, line);
			istringstream iss(line);
			while (iss >> value)
			{
				values.push_back(value);
			}
			add(rootDecision, rootOutput, attributes, values);
		}
	}
}

void add(NodeDecision * & rootDecision,
	NodeOutput * & rootOutput,
	const vector<string> & attributes,
	const vector<double> & values)
{
	string attribute = match(rootDecision, attributes, values);
	add(rootOutput, attribute, values);
}

void add(NodeOutput * & rootOutput, const string & attribute, const vector<double> & values)
{
	if (!rootOutput)
	{
		rootOutput = new NodeOutput;
		rootOutput->left = nullptr;
		rootOutput->right = nullptr;
		rootOutput->name = attribute;
		rootOutput->values.push_back(values);
	}
	else
	{
		if (attribute == rootOutput->name)
			rootOutput->values.push_back(values);
		else if (attribute < rootOutput->name)
			add(rootOutput->left, attribute, values);
		else
			add(rootOutput->right, attribute, values);
	}
}

string match(NodeDecision * & rootDecision,
	const vector<string> & attributes,
	const vector<double> & values)
{
	NodeDecision * tempNode = rootDecision;
	while (true)
	{
		double value = values[findPosition(attributes,
			tempNode->decision.condition.attribute)];
		if (value >= tempNode->decision.condition.value)
		{
			if (tempNode->decision.hasRightChild)
				tempNode = tempNode->right;
			else
				return tempNode->decision.indexOutYes;
		}
		else
		{
			if (tempNode->decision.hasLeftChild)
				tempNode = tempNode->left;
			else
				return tempNode->decision.indexOutNo;
		}
	}
}

void writeToFile(NodeOutput * & rootOutput)
{
	fstream file("Output.txt", ios::out);
	write(rootOutput, file);
}

void write(NodeOutput * & rootOutput, fstream & file)
{
	if (rootOutput)
	{
		file << rootOutput->name << endl;
		for (int i = 0; i < rootOutput->values.size(); i++)
		{
			for (int j = 0; j < rootOutput->values[i].size(); j++)
			{
				file << rootOutput->values[i][j] << " ";
			}
			file << endl;
		}
		write(rootOutput->left, file);
		write(rootOutput->right, file);
	}
}

void clear(NodeOutput * & nodeOutput)
{
	if (nodeOutput)
	{
		clear(nodeOutput->left);
		clear(nodeOutput->right);

		delete nodeOutput;
		nodeOutput = nullptr;
	}
}

int findPosition(const vector<string> & vector, const string & arg)
{
	auto position = find(vector.begin(), vector.end(), arg);
	if (position == vector.end())
	{
		return -1;
	}
	else
	{
		return distance(vector.begin(), position);
	}
}