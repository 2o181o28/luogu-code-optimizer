#include<bits/stdc++.h>
using namespace std;

auto f(integral auto x){return x*x;}

int main(){
	vector<future<void>> v;
	for(int i=1;i<=10;i++){
		v.push_back(async(launch::async,[=](){
			this_thread::sleep_for(100ms);
			printf("%d\n",f(i));
		}));
	}
	for(auto&x:v)x.wait();
	return 0;
}
