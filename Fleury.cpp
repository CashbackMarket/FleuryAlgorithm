#include<iostream>
#include<vector>
using namespace std;

class Graph{
	
	int vertex; // number of vertices
	vector<vector<int>> adj; // adjacency list
	
	public:
		
		//Inicializando o Grafo
		Graph(int v){
			vertex = v;
			adj = vector<vector<int>>(v+1);
		}
		
	
		void addEdge(int u, int v){
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		
		void removeEdge(int v,int u){
			
	
			for(int i=0;i<adj[v].size();++i){
				if(adj[v][i]==u){
					swap(adj[v][i], adj[v][adj[v].size()-1]);
					adj[v].pop_back();
					break;
				}
			}
			
			
			for(int i=0;i<adj[u].size();++i){
				if(adj[u][i]==v){
					swap(adj[u][i], adj[u][adj[u].size()-1]);
					adj[u].pop_back();
					break;
				}
			}
			
		}
		
		
		void printEulerPathCircuit(){
			
			int odd = 0; // number of vertices with odd degree
			int oddVertex = 0; // it stores vertex with odd degree if it exists
			
			for(int i=1;i<=vertex;++i){
				if(adj[i].size()%2==1){
					++odd;
					oddVertex = i;
				}
			}
			
			if(odd==0){
			
				cout<<"Euler Circuit: ";
	
				printEuler(1);
			}
			else if(odd==2){
				
				cout<<"Euler Path: ";
				printEuler(oddVertex);
			}
			else{
				cout<<"Euler Path/Circuit Doesn't Exist"<<endl;
			}
			
		}
		
	
		void printEuler(int v){
			
		
			cout<<" "<<v<<" ";
			
		
			if(adj[v].size()==0){
				return;
			}
			
		
			if(adj[v].size()==1){
				int u = adj[v][0];
				removeEdge(v, u);
				printEuler(u);
				return;
			}	
						
		
			for(auto u: adj[v]){

				if(isValidEdge(v, u)){
				
					removeEdge(v, u);
					printEuler(u);
					return;
				}
				
			}
			
		}
		
	
		bool isValidEdge(int v, int u){
			
			int c1, c2;
			c1 = c2 = 0;
			vector<bool> visited;
			
		
			removeEdge(v, u);
			visited = vector<bool>(vertex+1,false);
			c1 = countConnectedVertices(u, visited);
			
			addEdge(v, u);
			visited = vector<bool>(vertex+1,false);
			c2 = countConnectedVertices(u, visited);
			
			
			if(c2 == c1) return true;
			else		 return false;
			
		}
		
	
		int countConnectedVertices(int u, vector<bool> &visited){
			
			visited[u] = true;
			int count = 1;
			for(auto v: adj[u]){
				if(!visited[v]){
					count += countConnectedVertices(v, visited);
				}
			}
			return count;
			
		}
	
};

int main()
{
	// graph G, containing 7 vertices from 1 to 7.
	Graph G(7);
	

	G.addEdge(1,2);
	G.addEdge(1,3);
	G.addEdge(1,4);
	G.addEdge(1,6);
	G.addEdge(2,3);
	G.addEdge(2,5);
	G.addEdge(2,7);
	G.addEdge(5,6);
	G.addEdge(6,7);
	

	G.printEulerPathCircuit();
}
