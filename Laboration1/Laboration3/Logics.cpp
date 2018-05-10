#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

//SAME BUT USING VECTORS

struct Clause {
	//, i.e &&, ||
	Clause() = default;

	Clause(vector<string> _p, vector<string> _n) : p{ _p }, n{ _n } {
		vector<string> intersection;
		set_intersection(p.begin(), p.end(), n.begin(), n.end(), inserter(intersection, intersection.begin()));

		if (!intersection.empty()) {
			vector<string> temp, temp2;
			set_difference(begin(p), end(p), begin(intersection), end(intersection), inserter(temp, temp.end()));
			set_difference(begin(n), end(n), begin(intersection), end(intersection), inserter(temp2, temp2.end()));
			p = temp;
			n = temp2;
		}

		//Remove duplicates.
		RemoveDuplicates();

	};


	void RemoveDuplicates() {
		sort(p.begin(), p.end());
		p.erase(unique(p.begin(), p.end()), p.end());

		sort(n.begin(), n.end());
		n.erase(unique(n.begin(), n.end()), n.end());
	}

	void Sort() {
		sort(p.begin(), p.end());
		sort(n.begin(), n.end());
	}

	bool IsEmpty() {
		if (p.empty() && n.empty())
			return true;
		else
			return false;
	}


	bool operator<(const Clause &s) const
	{
		return (p < s.p);
	}

	bool operator==(const Clause &s) const
	{
		return (p == s.p && n == s.n);
	}

	friend ostream& operator<<(ostream& out, const Clause& c);

	vector<string> p;
	vector<string> n;

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
	vector<string> _An, _Ap, _Bn, _Bp;
	vector<string> intersection1, intersection2;

	set_intersection(A.p.begin(), A.p.end(), B.n.begin(), B.n.end(), inserter(intersection1, intersection1.begin())); //A.p inters B.n
	set_intersection(A.n.begin(), A.n.end(), B.p.begin(), B.p.end(), inserter(intersection2, intersection2.begin())); //A.p inters B.n

																													  //If the intersections are empty:
	if (intersection1.empty() && intersection2.empty()) {
		// << "1st" << endl;
		cout << "empty intersections" << endl;
		return Clause(); //false (empty clause)
	}

	if (!intersection1.empty()) {

		set_difference(begin(A.p), end(A.p), begin(intersection1), end(intersection1), inserter(_Ap, _Ap.end()));
		set_difference(begin(B.n), end(B.n), begin(intersection1), end(intersection1), inserter(_Bn, _Bn.end()));
		A.p = _Ap;
		B.n = _Bn;

	}
	else {

		set_difference(begin(A.n), end(A.n), begin(intersection2), end(intersection2), inserter(_An, _An.end()));
		set_difference(begin(B.p), end(B.p), begin(intersection2), end(intersection2), inserter(_Bp, _Bp.end()));

		A.n = _An;
		B.p = _Bp;

	}

	//Create clause 
	Clause C;

	set_union(A.p.begin(), A.p.end(), B.p.begin(), B.p.end(), inserter(C.p, C.p.end()));
	set_union(A.n.begin(), A.n.end(), B.n.begin(), B.n.end(), inserter(C.n, C.n.end()));

	//cout << "C:" << C;

	//check if tautology
	vector<string> c_inters;
	set_intersection(C.p.begin(), C.p.end(), C.n.begin(), C.n.end(), inserter(c_inters, c_inters.begin())); //A.p inters B.n

	if (!c_inters.empty()) {
		//cout << "2nd" << endl;
		cout << "Tautology" << endl;
		return Clause();
	}

	C.RemoveDuplicates();

	return C;
}

//A is a subset of B
bool Subsumes(Clause A, Clause B) {
	A.Sort();
	B.Sort();

	/*cout << "Bp: " << endl;
	for (auto i : B.p)
	cout << i << " ";
	cout<< endl << "Ap: " << endl;
	for (auto i : A.p)
	cout << i << " ";
	cout << endl << "bn: " << endl;
	for (auto i : B.n)
	cout << i << " ";
	cout << endl << "An: " << endl;
	for (auto i : A.n)
	cout << i ;*/


	bool b1 = includes(B.p.begin(), B.p.end(), A.p.begin(), A.p.end());
	bool b2 = includes(B.n.begin(), B.n.end(), A.n.begin(), A.n.end());


	if (b1 && b2) {
		return true;
	}
	else {
		return false;
	}

}

bool StrictSubsumes(Clause A, Clause B) {
	vector<string> temp1, temp2;
	set_difference(begin(B.p), end(B.p), begin(A.p), end(A.p), inserter(temp1, temp1.end())); // The elements in B that are not in A
	set_difference(begin(B.n), end(B.n), begin(A.n), end(A.n), inserter(temp2, temp2.end()));

	/*bool b1 = !temp1.empty();
	bool b2 = !temp2.empty();
	cout << "B1: " << b1 << endl;
	cout << "B2: " << b2 << endl;*/

	if (Subsumes(A, B)) {

		if (!temp1.empty() || !temp2.empty())
			return true;
		else
			return false;
	}
	else
		return false;

}



vector<Clause> Incoperate_Clause(Clause A, vector<Clause> KB) {
	A.Sort();

	//cout << "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEj" << endl;

	for (auto B : KB) {
		if (Subsumes(B, A)) //B is a subset of A
			return KB;
	}


	for (auto B : KB) {
		//cout << "B: " << B;

		B.Sort();
		vector<string> temp1, temp2;
		set_difference(begin(A.p), end(A.p), begin(B.p), end(B.p), inserter(temp1, temp1.end()));
		set_difference(begin(A.n), end(A.n), begin(B.n), end(B.n), inserter(temp2, temp2.end()));

		/*cout << endl << endl << "difference between Ap and Bp: " << endl;
		for (auto i : temp1)
			cout << i << " ";

		cout << endl << "difference between An and Bn: " << endl;
		for (auto i : temp2)
			cout << i << " ";

		cout << endl << endl;*/

		if (StrictSubsumes(A, B)) {
			vector<Clause> Btemp{ B }, KBtemp;
			set_difference(begin(KB), end(KB), begin(Btemp), end(Btemp), inserter(KBtemp, KBtemp.end()));

			//cout << endl << endl << "difference between KB and B: " << endl;
			//for (auto i : KBtemp)
			//	cout << i << " ";

			//cout << endl << endl;


			KB = KBtemp;
		}
	}

	/*cout << "Knowledge base before: " << endl;
	for (auto i : KB)
	cout << i;
	cout << "A: " << A;
*/


	vector<Clause> Atemp{ A }, KBtemp2;
	set_union(begin(KB), end(KB), begin(Atemp), end(Atemp), inserter(KBtemp2, KBtemp2.end()));
	KB = KBtemp2;
	

	/*cout << "Knowledge base after: " << endl;
	for (auto i : KB)
		cout << i;
*/
	return KB;
}

vector<Clause> Incoperate(vector<Clause> S, vector<Clause> KB) {

	//cout << "Knowledge base: " << endl;
	//for (auto i : KB)
	//	cout << i;

	for (Clause A : S) {
		//cout << "A: " << A;

		KB = Incoperate_Clause(A, KB);
	}
	//cout << "Incoperate finished" << endl;
	return KB;
}

//Solve the knowledge base
vector<Clause> Solver(vector<Clause> KB) {
	vector<Clause> _KB;
	vector<Clause> _S;
	/*cout << "Knowledge base before: " << endl;
	for (auto i : KB)
	cout << i;*/
	int Counter = 1;
	do {
		sort(KB.begin(), KB.end());
		_KB = KB;
		vector<Clause> S;

		_S = S;

		for (int i = 0; i < KB.size(); i++) {
			Clause A = KB[i];


			for (int j = i + 1; j < KB.size(); j++) {
				/*cout << "*************************" << endl;
				cout << "iteration " << Counter << endl;*/
				Counter++;
				Clause B = KB[j];

				Clause C = Resolution(A, B);

				//cout << "C:" << C;

				//if (C.IsEmpty()) {
				//	cout << "C is empty!" << endl;
				//}
				//else {
				//	cout << "C NOT empty!" << endl;
				//	/*cout << "Knowledge base: " << endl;
				//	for (auto i : KB)
				//	cout << i;
				//	*/
				//}


				if (!(C.n.empty() && C.p.empty())) {
					//cout << "size:" << KB.size() << endl;
					vector<Clause> temp{ C }, temp2;
					set_union(S.begin(), S.end(), temp.begin(), temp.end(), inserter(temp2, temp2.begin()));

					/*cout << "temp: " << endl;
					for (auto i : temp)
					cout << i;*/
					S = temp2;

					/*cout << "S: ";
					for (auto i : S)
						cout << i;*/
				}
			}
		}

		//cout << "adsuhilaf:" << endl;

		/*cout << "S: ";
		for (auto i : S)
		cout << i;*/

		if ((S.empty())) {
			//cout << "SMall" << endl;
			return KB;
		}

		//Incoperate
		KB = Incoperate(S, KB); //This returns the same ????????
		//cout << "adsuhilasdkjhauhdouwdqahoiwhodhqiuahduaf:" << endl;

		/*if (KB == _KB)
			cout << "YES same" << endl;*/

	} while (_KB != KB);


};



int main() {
	//vector<string> a{ "a" };
	//vector<string> b{ "b" };
	//vector<string> c{  };


	//Clause A(b, a);
	//Clause B(a, c);
	////Clause C(b, c);

	//cout << "A: " << A;
	//cout << "B: " << B;

	//set<Clause> KB{ A, B };

	//Clause resol = Resolution(A, B);
	//cout << resol;

	vector<string> a{ "a" };
	vector<string> not_b{ "b" };
	vector<string> ac{ "a", "c" };
	vector<string> not_c{ "c" };
	vector<string> all{ "a", "b","c" };
	vector<string> none{};

	Clause A(a, not_c); //(a & -c)
	Clause B(ac, not_b); //(a & c & -b)
	Clause C(all, none); //(a & b & c)
						 //Clause D(d, a);

	vector<Clause> KB{ A, B, C };

	/*if (StrictSubsumes(B,  A))
	cout << "Yes";
	else
	cout << "No.";*/


	cout << "Knowledge base after: " << endl;
	for (auto i : KB)
	cout << i;
	


	vector<Clause> res = Solver(KB);
	cout << endl << "Solver finished. " << endl;

	cout << endl << "Resulting solution: " << endl;

	if (res.empty())
		cout << "Empty" << endl;
	else {

		for (auto s : res) {
			cout << s << endl;
		}
	}




	cin.get();
}
