#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define si size()
#define bk back()
#define popb pop_back()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl "\n"
#define lb lower_bound
#define ub upper_bound
#define emp empty()
#define beg begin()
#define en end()
#define forl(i,a,n) for(int i=a;i<n;i++)
#define rfor(i,n,a) for(int i=n;i>=a;i--)
#define fore(i,a,n) for(int i=a;i<=n;i++)
ll mod=1e9+7;
int prec(char c) 
{ 
    if(c == '^') 
    return 3; 
    else if(c=='$')
	return 4;
    else if(c == '*' || c == '/') 
    return 2; 
    else if(c == '+' || c == '-') 
    return 1; 
    else
    return -1; 
} 
struct node{
	int x;
	char opr;
	bool b;
};
struct et{
	node val;
	et * left;
	et * right;
};

et * make_tree(vector<node>v){
	stack<et *> s;
	et *t, *t1, *t2;
	forl(i,0,v.si){
		if(v[i].b){
			t=new et;
			t->val=v[i];
			t1=s.top();
			s.pop();
			t2=s.top();
			s.pop();
			t->right=t1;
			t->left=t2;
			s.push(t);
		}
		else{
			t=new et;
			t->val=v[i];
			t->left=NULL;
			t->right=NULL;
			s.push(t);
		}
	}
	return s.top();
}
stack<node>st;
vector<node> intopost(vector<node>v){
	vector<node> ans;
	forl(i,0,v.si){
		if(v[i].b){
			char c=v[i].opr;
			if(c=='('){
				st.push(v[i]);
			}
			else if(c==')'){
				while(st.top().opr!='('){
					ans.pb(st.top());
					st.pop();
				}
				st.pop();
			}
			else{
				while(st.top().opr!='('&&prec(c)<=prec(st.top().opr)){
					if(prec(c)==3&&prec(st.top().opr)==3) break;
					if(prec(c)==4&&prec(st.top().opr)==4) break;
					ans.pb(st.top());
					st.pop();
				}
				st.push(v[i]);
			}
		}
		else{
			ans.pb(v[i]);
		}
	}
	return ans;
	
}
int eval(et * root){
	if(root==NULL) return 0;
	if(root->left==NULL&&root->right==NULL){
		return root->val.x;
	}
	int l=eval(root->left);
	int r=eval(root->right);
	if(root->val.opr=='+') return l+r;
	else if(root->val.opr=='-'||root->val.opr=='$') return l-r;
	else if(root->val.opr=='*') return l*r;
	else if(root->val.opr=='/') return l/r;
	else return pow(l,r);
}
int main(){
	fastio;
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<string> key;
		vector<int> val;
		while(n--){
			string var="",curr_var="";
			string s="(";
			string tmps;
			cin>>tmps;
			int c=1; int check=1;
			forl(i,0,tmps.si){
				if(!(tmps[i]>='a'&&tmps[i]<='z'||tmps[i]>='A'&&tmps[i]<='Z')&&(tmps[i]!='=')){
					if(curr_var.si!=0){
						int x=-1;
						forl(j,0,key.si){
							if(key[j]==curr_var){
								x=j; break;
							}
						}
						if(x==-1) {cout<<"CANT BE EVALUATED"<<endl; check=0;}
						else {s+=to_string(val[x]); curr_var="";}
					}
				}
				if(tmps[i]>='0'&&tmps[i]<='9'){
					c=0;
					s+=tmps[i];
				}
				else if(tmps[i]=='('||tmps[i]==')'){
					s+=tmps[i];
				}
				else if(tmps[i]>='a'&&tmps[i]<='z'||tmps[i]>='A'&&tmps[i]<='Z'){
					curr_var+=tmps[i];
				}
				else if(tmps[i]=='='){
					var=curr_var;
					curr_var="";
					continue;
				}
				else{
					if(c!=0&&tmps[i]=='-'){
						s+="0$";
					}
					else s+=tmps[i];
					c++;
				}
				if(check==0) break;
			}
			
			if(curr_var.si!=0){
				int x=-1;
				forl(j,0,key.si){
					if(key[j]==curr_var){
						x=j; break;
					}
				}
				if(x==-1){ cout<<"CANT BE EVALUATED"<<endl; check=0;}
				else {s+=to_string(val[x]); curr_var="";}
				    
			}
			if(check==0) continue;
			s+=')';
			int a=0,o=0;
			string curr="";
			vector<node> v;
			forl(i,0,s.si){
				if(s[i]>='0'&&s[i]<='9'){
					curr+=s[i];
				}
				else{
					if(!curr.si&&s[i]=='-'){
						curr+=s[i];
					}
					else if(curr.si==1&&curr[0]=='-'){
						curr+='1';
						s[i-1]='*';
						i-=2;
					}
					else {
						if(curr.si){
						node n;
						n.b=0;
						n.x=stoi(curr);
						v.pb(n);}
						curr="";
						node n;
						n.opr=s[i];
						n.b=1;
						v.pb(n);
					}
				}
			}
			if(curr.si){
				node n;
				n.b=0;
				n.x=stoi(curr);
				v.pb(n);
			}
			vector<node> post=intopost(v);
			et * root=make_tree(post);
			if(var.si==0)cout<<eval(root)<<endl;
			else{
				key.pb(var);
				val.pb(eval(root));
			} 
		}
	}
	return 0;
}
