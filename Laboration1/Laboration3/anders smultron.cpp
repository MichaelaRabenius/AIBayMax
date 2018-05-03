#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

class clause {
public:
	
	clause() {};
	~clause() {};

	clause(set<string> S1, set<string> S2) {

		p = S1;
		n = S2; 

	}

	set<string> p; // positive literals are saved here
	set<string> n; // negative literals are saved here
};


clause Resolution(clause A, clause B)
{
	set<string> c1;
	set<string> c2;

	// check if A & B have any elements in common. 
	set_intersection(A.p.begin(), A.p.end(), B.p.begin(), B.p.end(), inserter(c1, c1.begin()));
	set_intersection(B.n.begin(), B.n.end(), A.n.begin(), A.n.end(), inserter(c2, c2.begin()));
	
	// if they have elements in common, remove duplicates and concatenate 
	// if nothing in common, they already resolved
	if (!c1.empty() && !c2.empty())
	{
		// do stuff 
		clause C; // this is what i will return. 

		// compare if A.p & B.n have any elements in common
		clause AB;
		set_intersection(A.p.begin(), A.p.end(), B.n.begin(), B.n.end(), inserter(AB.p, AB.p.begin()));

		// if the do have elements in common, 
		if (!AB.empty())
		{
			clause Atemp;
			set_union(AB.p.begin(), AB.p.end(), AB.n.begin(), AB.n.end(), inserter(AB.p, AB.p.begin()));
		}
		

		//if intersection( A.p, B.n) == empty

		// Atemp.p = ( A.p - intersection( A.p, B.n) )
		// Btemp.p = ( B.p - intersection( B.p, A.n) )

		// C.p = Atemp.p + Btemp.p

		// same thing for negative part. 

		clause atemp;
		clause btemp;

		// setup C with c.n and c.p

		// do A.p and  B.n have anything in common? if so,ta bort det som tar ut varandra. 
		set_intersection(A.p.begin(), A.p.end(), B.n.begin(), B.n.end(), inserter(atemp.p, atemp.p.begin()));
		//set_intersection(A.p.begin(), A.p.end(), B.n.begin(), B.n.end(), inserter(C.n, C.n.begin()));

		// 


		return C;

	}
	else
	{
		//return false?
	}

}

int main()
{
	set<string> a{ "a", "b" };
	set<string> b{ "c", "d" };
	clause A(a,b); // class A should now be ( a & b & c' & d' )

	set<string> c{ "a", "d" };
	set<string> d{ "b", "c" };
	clause B(c, d);


	clause temp = Resolution(A, B);



}