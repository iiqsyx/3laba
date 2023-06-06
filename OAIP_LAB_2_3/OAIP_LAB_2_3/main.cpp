#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#define MAX_VALUE_LENGTH 20
#define M 20

struct BinaryTree {
	char* value;
	int n; 
	struct BinaryTree* leftTree;
	struct BinaryTree* rightTree;
};

struct Stack
{
	BinaryTree* tree;
	Stack* stack;
};

BinaryTree* CreateBinaryTree(BinaryTree* tree);
void AddNode(BinaryTree* tree);
BinaryTree* DeleteNode(BinaryTree* tree);
void ViewTreeRecursively(BinaryTree* tree);
void ViewTreeUsingStack(BinaryTree* tree);
void CountNodesAtNLevel(BinaryTree* tree);
int get(BinaryTree* tree, int currentLevel, int nextLevel = 0);

void main() {
	setlocale(LC_ALL, "ru");

	BinaryTree* rootTree = NULL;
	int choice = 0;

	while (true)
	{
		system("cls");

		cout << "-~<3<3<3 Выберите операцию:" << endl;
		cout << "1| Создать дерево" << endl;
		cout << "2| Добавление элементов в дерево" << endl;
		cout << "3| Удаление любого элемента из дереева" << endl;
		cout << "4| Рекурсивный вывод содерживомого дерева" << endl;
		cout << "5| Нерекурсивный вывод содержимого дерева" << endl;
		cout << "6| Определить количество узлов на N-м уровне бинарного дерева" << endl;
		cout << endl;
		cout << "0| Выход" << endl;
		cout << "ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 0:  
			exit(0);
			break;
		case 1:
			rootTree = CreateBinaryTree(rootTree);
			break;
		case 2:
			AddNode(rootTree);
			break;
		case 3:
			DeleteNode(rootTree);
			break;
		case 4:
			ViewTreeRecursively(rootTree);
			system("pause");
			break;
		case 5:
			ViewTreeUsingStack(rootTree);
			system("pause");
			break;
		case 6:
			CountNodesAtNLevel(rootTree);
			break;
		}
	}
}

BinaryTree* CreateBinaryTree(BinaryTree* tree)
{
	if (tree) 
	{
		cout << "<3 Бинарноее дерево уже создано!" << endl;
		return tree;
	}

	if (!(tree = (BinaryTree*)calloc(1, sizeof(BinaryTree)))) 
	{
		cout << "<3 Нет свободной памяти!" << endl;
		return NULL;
	}

	cout << "-~<3<3<3 Введите информацию в корень дерева: ";
	tree->value = (char*)calloc(1, sizeof(char) * MAX_VALUE_LENGTH);
	cin >> tree->value;
	tree->n = 1;
	return tree;
}

void AddNode(BinaryTree* tree)
{
	struct BinaryTree* leftSubtree;
	struct BinaryTree* rightSubtree;
	char* value;
	int resultOfComparingTwoStrings;
	int exitCode; // 1 - если надо выйти из цикла

	if (!tree) 
	{
		cout << "Нет корня дерева!" << endl;
		return;
	}

	do
	{
		cout << "-~<3<3<3 Введите информацию в очередной узел дерева (0 - выход): ";
		value = (char*)calloc(1, sizeof(char) * MAX_VALUE_LENGTH);
		cin >> value;

		if (*value == '0') return;

		leftSubtree = tree;
		exitCode = 0;

		do
		{
			if (!(resultOfComparingTwoStrings = strcmp(value, leftSubtree->value))) 
			{
				leftSubtree->n++;
				exitCode = 1;
			}
			else 
			{
				if (resultOfComparingTwoStrings < 0)
				{
					if (leftSubtree->leftTree) leftSubtree = leftSubtree->leftTree;
					else exitCode = 1;
				}
				else
				{
					if (leftSubtree->rightTree) leftSubtree = leftSubtree->rightTree;
					else exitCode = 1;
				}
			}
		} while (exitCode == 0);

		if (resultOfComparingTwoStrings) {
			if (!(rightSubtree = (struct BinaryTree*)calloc(1, sizeof(BinaryTree)))) {
				cout << "Нет свободной памяти!" << endl;
				return;
			}

			if (resultOfComparingTwoStrings < 0) leftSubtree->leftTree = rightSubtree;
			else leftSubtree->rightTree = rightSubtree;

			rightSubtree->value = (char*)calloc(1, sizeof(char) * MAX_VALUE_LENGTH);
			strcpy_s(rightSubtree->value, strlen(value) + 1, value);
			rightSubtree->n = 1;
		}
		free(value);
	} while (true);
}

BinaryTree* DeleteNode(BinaryTree* tree)
{
	struct BinaryTree* tree1;
	struct BinaryTree* tree2;
	struct BinaryTree* tree3;
	char* value;
	int resultOfComparingTwoStrings;
	int exitCode;

	if (!tree)
	{
		cout << "-~<3<3<3 Дерево не создано!" << endl;
		return NULL;
	}

	cout << "-~<3<3<3 Введите информацию в очередной узел дерева (0 - выход): ";
	value = (char*)calloc(1, sizeof(char) * MAX_VALUE_LENGTH);
	cin >> value;

	if (!*value) return NULL;

	tree2 = tree1 = tree;
	exitCode = 0;

	do
	{
		if (!(resultOfComparingTwoStrings = strcmp(value, tree1->value)))
		{
			exitCode = 1;
		}

		if (resultOfComparingTwoStrings < 0)
		{
			if (tree1->leftTree) 
			{
				tree2 = tree1;
				tree1 = tree1->leftTree;
			}
			else
			{
				exitCode = 1;
			}
		}

		if (resultOfComparingTwoStrings > 0)
		{
			if (tree1->rightTree)
			{
				tree2 = tree1;
				tree1 = tree1->rightTree;
			}
			else
			{
				exitCode = 1;
			}
		}
	} while (!exitCode);

	free(value);

	if (resultOfComparingTwoStrings)
	{
		cout << "<3<3<3 Требуемый узел не найден!" << endl;
		return tree;
	}
	else
	{
		resultOfComparingTwoStrings = strcmp(tree1->value, tree2->value);
		tree3 = tree1;

		if (resultOfComparingTwoStrings < 0)
		{
			tree3 = tree1->rightTree;
			while (tree3->leftTree) tree3 = tree3->leftTree;
			tree2->leftTree = tree1->rightTree;
			tree3->leftTree = tree1->leftTree;
		}
		else
		{
			tree3 = tree1->leftTree;
			while (tree3->rightTree) tree3 = tree3->rightTree;
			tree2->rightTree = tree1->leftTree;
			tree3->rightTree = tree1->rightTree;
		}
	}
}

void ViewTreeRecursively(BinaryTree* tree)
{
	if (tree)
	{
		cout << "<3 Узел содержит: " << tree->value << ", число встреч: " << tree->n << endl;

		if (tree->leftTree) ViewTreeRecursively(tree->leftTree);
		cout << "<3 Узел содержит: " << tree->value << ", число встреч: " << tree->n << endl;

		if (tree->rightTree) ViewTreeRecursively(tree->rightTree);
		cout << "<3 Узел содержит: " << tree->value << ", число встреч: " << tree->n << endl;
	}
}

void ViewTreeUsingStack(BinaryTree* tree)
{
	Stack* stack = NULL;
	Stack* tempStack = NULL;

	int exitCode = 1;

	for (int i = 0; i < 2; i++) 
	{
		stack = (Stack*)calloc(1, sizeof(Stack));
		stack->tree = tree;
		stack->stack = tempStack;
		tempStack = stack;
	}

	cout << "<3 Узел содержит: " << tree->value << ", число встреч: " << tree->n << endl;

	while (stack)
	{
		do
		{
			if (exitCode && tree->leftTree) tree = tree->leftTree;
			else if (tree->rightTree) tree = tree->rightTree;
			
			exitCode = 1;

			if (tree->leftTree && tree->rightTree)
			{
				tempStack = stack;
				stack = (Stack*)calloc(1, sizeof(Stack));
				stack->tree = tree;
				stack->stack = tempStack;
			}

			cout << "Узел содержит: " << tree->value << ", число встреч: " << tree->n << endl;
		} while (tree->leftTree || tree->rightTree);

		tree = stack->tree;
		tempStack = stack->stack;

		free(stack);

		stack = tempStack;
		if (tree->rightTree) exitCode = 0;
	}
}

void CountNodesAtNLevel(BinaryTree* tree)
{
	int currentLevel = 0;
	int max_levels = 0;
	int amountOfNodes = 0;

	while ((get(tree, currentLevel++)) != 0) {
		max_levels = currentLevel;
	}

	int choice = 0;

	do
	{
		cout << "<3<3<3 Введите нужный уровень (максимум - " << max_levels << "; 0 - выход): ";
		cin >> choice;

		switch (choice)
		{
		case 0:
			return;
			break;
		default: 
			if (choice < 0) 
			{
				cout << "<3<3<3 Неверно введена строка!" << endl;
				break;
			}

			amountOfNodes = get(tree, choice);
			cout << "<3<3<3 Кол-во узлов на уровне " << choice << " равно " << amountOfNodes << endl;
			break;
		}
	} while (true);
}

int get(BinaryTree* tree, int currentLevel, int nextLevel)
{
	if (currentLevel == nextLevel)  return 1;
	return ((tree->leftTree) ? get(tree->leftTree, currentLevel, nextLevel + 1) : 0) + ((tree->rightTree) ? get(tree->rightTree, currentLevel, nextLevel + 1) : 0);
}