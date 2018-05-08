#include <iostream>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

struct Clause {
	//, i.e &&, ||
	Clause() = default;

	Clause(set<string> _p, set<string> _n) : p{ _p }, n{ _n } {
		set<string> intersection;
		set_intersection(p.begin(), p.end(), n.begin(), n.end(), inserter(intersection, intersection.begin()));

		if (!intersection.empty()) {
			set<string> temp, temp2;
			set_difference(begin(p), end(p), begin(intersection), end(intersection), inserter(temp, temp.end()));
			set_difference(begin(n), end(n), begin(intersection), end(intersection), inserter(temp2, temp2.end()));
			p = temp;
			n = temp2;
		}
	};
	
	
	bool operator<(const Clause &s) const
	{
		return (p < s.p);
	}

	bool operator==(const Clause &s) const
	{
		return (p == s.p && n == s.n);
	}

	friend ostream& operator<<(ostream& out, const Clause& c);

	set<string> p;
	set<string> n;

};

ostream& operator<<(ostream& out, Clause& c) {
	out << "================================" << endl;
	out << "Clause:" << endl << "positives: ";
	copy(c.p.begin(), c.p.end(), ostream_iterator<string>(out, " "));
	cout << endl << "negatives: ";
	copy(c.n.begin(), c.n.end(), ostream_iterator<string>(out, " "));
	out << endl << "================================" << endl;
	return out;
}


//find the resolution of two clauses
Clause Resolution(Clause A, Clause B) {
	Clause C;
	set<string> _An, _Ap, _Bn, _Bp;

	set<string> dest1, dest2, dest3;
	set_intersection(A.p.begin(), A.p.end(), B.n.begin(), B.n.end(), inserter(dest1, dest1.begin())); //A.p inters B.n
	set_intersection(A.n.begin(), A.n.end(), B.p.begin(), B.p.end(), inserter(dest2, dest2.begin())); //A.n inters B.p


	if (dest1.empty() && dest2.empty()) {
		//cout << "First if." << endl;
		return Clause();
	}

	if (!dest1.empty()) {
		set_difference(begin(A.p), end(A.p), begin(dest1), end(dest1), inserter(_Ap, _Ap.end()));
		set_difference(begin(B.n), end(B.n), begin(dest1), end(dest1), inserter(_Bn, _Bn.end()));
		
	}
	else {
		set_difference(begin(A.n), end(A.n), begin(dest1), end(dest1), inserter(_An, _An.end()));
		set_difference(begin(B.p), end(B.p), begin(dest1), end(dest1), inserter(_Bp, _Bp.end()));
	}

	//Create clause C
	set_union(_Ap.begin(), _Ap.end(), _Bp.begin(), _Bp.end(), inserter(C.p, C.p.end()));
	set_union(_An.begin(), _An.end(), _Bn.begin(), _Bn.end(), inserter(C.n, C.n.end()));

	cout << "C p" << endl;
	copy(C.p.begin(), C.p.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	cout << "C n" << endl;
	copy(C.n.begin(), C.n.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	//Check if C is a tautology
	set_intersection(C.p.begin(), C.p.end(), C.n.begin(), C.n.end(), inserter(dest3, dest3.begin())); //A.p inters B.n
	if (!dest3.empty()) {
		//cout << "second if." << endl;
		//copy(dest3.begin(), dest3.end(), ostream_iterator<string>(cout, " "));
		return Clause();
	}
	
	return C;
	

}

bool Subsumes(Clause A, Clause B) {
	bool b1 = includes(B.p.begin(), B.p.end(), A.p.begin(), A.p.end());
	bool b2 = includes(B.n.begin(), B.n.end(), A.n.begin(), A.n.end());
	if (b1 && b2) {
		return true;
	}
	else {
		return false;
	}

}

set<Clause> Incoperate_Clause(Clause A, set<Clause> KB) {

	for (Clause B : KB) {
		if (Subsumes(B, A)) { //Note order, may be wrong
			return KB;
		}
	}

	for (Clause B : KB) {
		set<string> temp1, temp2;
		set_difference(begin(A.p), end(A.p), begin(B.p), end(B.p), inserter(temp1, temp1.end()));
		set_difference(begin(A.n), end(A.n), begin(B.n), end(B.n), inserter(temp2, temp2.end()));

		if (Subsumes(A, B) && (!temp1.empty() || !temp2.empty())) {
			set<Clause> Btemp, KBtemp;
			Btemp.emplace(B);
			set_difference(begin(KB), end(KB), begin(Btemp), end(Btemp), inserter(KBtemp, KBtemp.end()));
			KB = KBtemp;
		}
	}

	set<Clause> Atemp{ A }, KBtemp;
	set_union(begin(KB), end(KB), begin(Atemp), end(Atemp), inserter(KBtemp, KBtemp.end()));
	KB = KBtemp;
	return KB;
}

set<Clause> Incoperate(set<Clause> S, set<Clause> KB) {

	for (Clause A : S) {
		KB = Incoperate_Clause(A, KB);
	}
	return KB;
}

//Solve the knowledge base
set<Clause> Solver(set<Clause> KB) {
	set<Clause> _KB = KB;
	do {
		set<Clause> S;
		set<Clause>::iterator iter;
		for (iter = KB.begin(); iter != KB.end(); iter++) {
			Clause A = *iter;
			iter++;
			Clause B = *iter;
			Clause C = Resolution(A, B);

			if (!(C.n.empty() && C.p.empty())) {
				set<Clause> temp{ C }, temp2;
				set_union(S.begin(), S.end(), temp.begin(), temp.end(), inserter(temp2, temp2.begin()));
				S = temp2;
			}
		}

		if ((S.empty())) {
			return KB;
		}
		//Incoperate
		KB = Incoperate(S, KB);

	} while (KB != _KB);
}


int main(){
	set<string> a{ "a", "b", "d"}; 
	set<string> b{ "b", "d"}; 
	set<string> c{ "c", "d", "e"};
	set<string> d{ "a", "d", "e" };

	Clause A(a, b);
	Clause B(c, b); 
	Clause C(b, c);
	Clause D(d, a);

	set<Clause> KB{ A, B, C, D };

	set<Clause> res = Solver(KB);

	if (res.empty())
		cout << "Empty" << endl;
	else {
		
		for (auto s : res) {
			cout << s << endl;
		}
	}

	/*cout << "Testing A: " << endl;
	//set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin())); //A.p inters B.n
	cout << "A positives: ";
	copy(A.p.begin(), A.p.end(), ostream_iterator<string>(cout, " "));
	cout << endl << "A negatives: ";
	copy(A.n.begin(), A.n.end(), ostream_iterator<string>(cout, " "));
	
	Clause C = Resolution(A, B);
	if (C.n.empty() && C.p.empty()) {
		cout << "\n No resolution clause";
	}
	else {
		cout << "C positives: ";
		copy(C.p.begin(), C.p.end(), ostream_iterator<string>(cout, " "));
		cout << endl << "C negatives: ";
		copy(C.n.begin(), C.n.end(), ostream_iterator<string>(cout, " "));
	}
	*/
	
	cin.get();
}