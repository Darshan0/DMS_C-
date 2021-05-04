#include "StringRelation.h"
#include <unistd.h>

/*
 * Assign SetMembers.
 */
void StringRelation::setInput(SetOfStrings *s)
{
	SetMembers=s;
}

/*
 * It splits a pair "a,b" into a vector of strings "a", "b".
 * Returns the string vector.
 */
vector<string> StringRelation::makeTokens(string pair){
	vector<string> out;
	vector<string>::iterator p;
	
	char *a = new char [pair.length()+1];
	strcpy(a,pair.c_str());
	char* token = strtok(a,",");
			int index=0;
				while (token != NULL) {
					out.push_back(token);
					token = strtok(NULL, ",");
					index++;
				}
	return out;
}

/*
 * Returns the equivalence class as a set object.
 */
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
	// TODO:
	SetOfStrings *out = new SetOfStrings();
	vector<vector<string>> relationPairs ; 
	for(int j = 0 ; j < elements.size() ; j++){
		relationPairs.push_back(makeTokens(elements[j]));
	}

	for(auto& row:relationPairs){
	
		if(row[0]==element){
			out->insertElement(row[1]);
		}
		if(row[1]==element){
			out->insertElement(row[0]);
		}
		
	}
	return out;
}

/*
 * Returns true if the relation is reflexive.
 * Otherwise, returns false.
 */
bool StringRelation::isReflexive(){


	bool success = true;

	int setMembersSize = SetMembers->size();
	
	vector<vector<string>> reflexivePairs ; 
	
	vector<vector<string>> relationPairs ;

	for(int i = 0 ; i < setMembersSize ; i++){
		string value = SetMembers->returnElement(i);
		reflexivePairs.push_back(makeTokens(value+","+value));
	}

	for(int j = 0 ; j < elements.size() ; j++){
		relationPairs.push_back(makeTokens(elements[j]));
	}

	for(int k = 0 ; k < reflexivePairs.size() ; k++){
		if(!(find(relationPairs.begin(), relationPairs.end(), reflexivePairs[k]) != relationPairs.end())){
			success = false;
			break;
		}
	}
	
	return success;

}

/*
 * Returns true if the relation is symmetric.
 * Otherwise, returns false.
 */
bool StringRelation::isSymmetric(){
	
	bool success = true;

	int setMembersSize = SetMembers->size();

	vector<vector<string>> relationPairs ; 


	for(int j = 0 ; j < elements.size() ; j++){
		relationPairs.push_back(makeTokens(elements[j]));
	}

	for(auto& row:relationPairs){
		vector<string> reverseRelationPair(row.rbegin(),row.rend());
		if(!(find(relationPairs.begin(), relationPairs.end(), reverseRelationPair ) != relationPairs.end())){
			success = false;
			break;
		}
	}
	return success;
}

/*
 * Returns true if the relation is transitive.
 * Otherwise, returns false.
 */
bool StringRelation::isTransitive(){
	// TODO:
	bool success = true;

	int setMembersSize = SetMembers->size();

	vector<vector<string>> relationPairs ; 


	for(int j = 0 ; j < elements.size() ; j++){
		relationPairs.push_back(makeTokens(elements[j]));
	}

	for(auto& row:relationPairs){
		string a = row[0];
		string b = row[1];
		for(auto& subrow:relationPairs){
			if (subrow[0] == row[1]){
				string c = subrow[1];
				if(!(find(relationPairs.begin(), relationPairs.end(), makeTokens(a+","+c) ) != relationPairs.end())){
					success = false;
					break;
				}
			}
		}
		
	}

	return success;
}

/*
 * Returns true if the relation is the equivalence relation.
 * Otherwise, returns false.
 */
bool StringRelation::isEquivalence(){

	// TODO:
	bool reflexive = isReflexive();
	bool symmetric = isSymmetric();
	bool transitive = isTransitive();
	if(reflexive && symmetric && transitive){
		return true;
	}else{
		return false;
	} 
}
