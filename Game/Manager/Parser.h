#pragma once
namespace Parser
{
	using namespace std;
	map<string, map<string, string>> Parse(FILE *pFile);
}