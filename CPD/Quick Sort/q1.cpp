#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

void print_array(int C[], int tam)
{
	printf("[");
	for (int i = 0; i < tam - 1; i++)
	{
		printf("%d, ", C[i]);
	}
	printf("%d]", C[tam - 1]);
}

int main(int argc, const char *argv[])
{

	return 0;
}