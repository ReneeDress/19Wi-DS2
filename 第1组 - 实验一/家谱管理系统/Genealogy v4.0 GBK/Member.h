#ifndef __MEMBER_H__
#define __MEMBER_H__

#include <string>

struct MemberData
{
	string name;
	string birth;
    bool marriage;
    string address;
    bool alive;
    string death;
    int generation;
};

struct Member
{
	MemberData person;
	Member *firstChild;
	Member *nextSibling;

	Member();
	Member(MemberData pers, Member *fChild = NULL, Member *nSibling = NULL);	
		
};

Member::Member()
{
	firstChild = nextSibling = NULL;
}

Member::Member(MemberData pers, Member *fChild, Member *nSibling)
{
	person = pers;	
	firstChild = fChild;
	nextSibling = nSibling;	
}

#endif
