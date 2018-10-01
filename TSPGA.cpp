#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
float cities[1000][2];
int index[1000][1], pop1[1000][1], pop_shuffle[1000][250], cross_child1[1000][1], cross_child2[1000][1],p1[1000][1], p2[1000][1], new_pop[1000][250], new_child[1000][400], pip = 4000, np = 1000, popo = 250, par = 200, mut = 50, path[1000][1];
float score[4000][1],dist_master[1000][1000],dist_pop[250][2], dist_pop_child[400][2] ,dis[1][1], disc1, disc2, childf[1000][1];
int main()
{
	srand(4);
//open file	
ifstream file;
	file.open("TSP21.txt");
 	if (file.is_open()) 
 	{
 		 for(int i = 0; i < np; ++i)
 		 {
 		 	for(int j = 0; j < 2; ++j)
 		 	{
 		 		file >> cities[i][j];
 		 		//cout << cities[i][j] << '\n';
			}
		}	
	}
//calculate master distance
for(int j = 0; j < np; j++)
{
	for(int i = 0; i < np; i++)
	{
		dist_master[i][j] = sqrt(pow((cities[i][0]-cities[j][0]),2) + pow((cities[i][1]-cities[j][1]),2));		
	}
}
//print distance master
/*long k = 0;
for(long j = 0; j < np; j++)
{
	for(long i = 0; i < np; i++)
	{
		cout<<dist_master[i][j] << " ";

	}
	cout << '\n';
}*/
//make index matrix
for(int i = 0; i < np; i++)
{
	index[i][0] = i+1;
}
//make general solution from index
int temp = 0;
for(int i = 0; i < np; i++)
{
	pop1[i][0] = index[i][0];
}
//shuffle and create population matrix
int ka = 0;
for(int l = 0 ; l < popo  ; l++)
{
	for(int j = np-1 ; j > 0  ; j--)
	{
		ka = rand()%(j+1);
		temp = pop1[j][0];
		pop1[j][0] = pop1[ka][0];
		pop1[ka][0] = temp;	
	}
	for(int i = 0; i < np; i++)
	{
		pop_shuffle[i][l] = pop1[i][0];
	}
}
//print population matrix
/*for(long i = 0; i < np; i++)
{
	for(long j = 0; j < popo; j++)
	{
		cout << pop_shuffle[i][j] << " ";
	}
	cout << '\n';
}*/
//loop for calculating generations
for(int i = 0; i < pip; i++)
{
	//calculate distance of population matrix
	for(int j = 0; j < popo; j++)
	{
		dis[0][0] = 0.0;
		for(int m = 1; m < np; m++)
		{
		dis[0][0] = dis[0][0] + dist_master[pop_shuffle[m][j] - 1][pop_shuffle[m-1][j] - 1]	;
		//cout << dist_master[4][1];
		}
		dist_pop[j][0] = dis[0][0];
		dist_pop[j][1] = j+1;
		//cout << dist_pop[j][0];
	}
	//print distance array
	/*for(long j = 0; j < popo; j++)
	{
		for(long i = 0; i < 2; i++)
		{
			cout << dist_pop[j][i] << " ";
		}
		cout << '\n';
	}*/	
	//cout << '\n';
	//sort distance array
	float temp1 = 0;
	int temp2 = 0;
	for(int j = 0; j < popo; j++)
	{
		for(int i = 1; i < popo; i++)
		{	
			if (dist_pop[i][0] > dist_pop[i-1][0])
			{	
				temp1 = dist_pop[i-1][0];
				temp2 = dist_pop[i-1][1];
				dist_pop[i-1][0] = dist_pop[i][0];
				dist_pop[i-1][1] = dist_pop[i][1];
				dist_pop[i][0] = temp1;
				dist_pop[i][1] = temp2;				
			}
		}
	}
	//print sorted distance array
	/*for(long j = 0; j < popo; j++)
	{
		for(long i = 0; i < 2; i++)
		{
			cout << dist_pop[j][i] << " ";
		}
		cout << '\n';
	}*/
	int be = 0;
	score[i][0] = dist_pop[0][0];
	for(int i = 0; i <np; i++)
	{
		be = dist_pop[0][1];
		path[i][0] = pop_shuffle[i][be - 1];
	}
	cout << score[i][0] << " ";
	//cout << '\n';
	//calculating inverse of distances and then the total sum
	float sum1 = 0;
	for(int i = 0; i < popo; i++)
	{
		dist_pop[i][0] = 1/dist_pop[i][0];
		sum1 = sum1 + dist_pop[i][0];
	}
	//print distance array
	/*for(long j = 0; j < popo; j++)
	{
		for(long i = 0; i < 2; i++)
		{
			cout << dist_pop[j][i] << " ";
		}
		cout << '\n';
	}*/
	//cout << '\n';
	//divide distance array for roulette selection
	for(int i = 0; i < popo; i++)
	{
		dist_pop[i][0] = dist_pop[i][0]/sum1;	
	}
	//cout << '\n';
	//print distance array
	/*for(long j = 0; j < popo; j++)
	{
		for(long i = 0; i < 2; i++)
		{
			cout << dist_pop[j][i] << " ";
		}
		cout << '\n';
	}*/
	//cout << '\n';
	//final distance for roulette selection
	for(int i = 1; i < popo; i++)
	{
		dist_pop[i][0] = dist_pop[i-1][0] + dist_pop[i][0];
	}
	//cout << '\n';
	//print final distance array
	/*for(long j = 0; j < popo; j++)
	{
		for(long i = 0; i < 2; i++)
		{
			cout << dist_pop[j][i] << " ";
		}
		cout << '\n';
	}*/
	//cout << '\n';
	//crossover 
	int ran1 = 0;
	int ran2 = 0;
	int ran11 = 0;
	int ran22 = 0;
	int start_co = 0;
	int end_co = 0;
	int p11 = 0;
	int p22 = 0;
	int paren_iter = 0;
	while (paren_iter < (2*par))
	{
		for(int j = 0; j < np; j++)
		{
			cross_child1[j][0] = 0;	
			cross_child2[j][0] = 0;
			p1[j][0] = 0;
			p1[j][0] = 0;			
		}
		ran1 = 0;
		ran2 = 0;
		ran11 = 0;
		ran22 = 0;
		p11 = 0;
		p22 = 0;
		/*ran1 = (rand()%999)/1000.000;
		ran2 = (rand()%999)/1000.000;
		cout << ran1 << '\n';
		cout << ran2 << '\n';
		for(long j = 0; j < np; j++)
		{
			if (ran1 <= dist_pop[j][0])
			{
				ran11 = dist_pop[j][1];
				cout << ran11 << '\n';
				break;
			}				
		}
		for(long j = 0; j < np; j++)
		{
			if (ran2 <= dist_pop[j][0])
			{
				ran22 = dist_pop[j][1];
				cout << ran22 << '\n';
				break;
			}				
		}*/
		ran1 = rand()%popo;
		ran2 = rand()%popo;
		ran11 = dist_pop[ran1][1];
		ran22 = dist_pop[ran2][1];
		//cout<<'\n';		
		if (ran11 != ran22)
		{
			//cout << ran1 << '\n';
			//cout << ran2 << '\n';
			p11 = ran11;
			p22 = ran22;
			//cout << p11 << '\n';
			//cout << p22 << '\n';
			//cout << '\n';	
			for(int j = 0; j < np; j++)
			{
				p1[j][0] = pop_shuffle[j][p11-1];
				p2[j][0] = pop_shuffle[j][p22-1];
				//cout << p1[j][0] << "  "	;
				//cout << p2[j][0] << '\n';
			}
			
			ran11 = rand()%np;
			ran22 = rand()%np;
			start_co = min(ran11,ran22);
			end_co = max(ran11,ran22);
						
			for(int j = start_co; j <= end_co; j++)
			{
				cross_child1[j][0] = p1[j][0];	
				cross_child2[j][0] = p2[j][0];
			}
			for(int j = 0; j < np; j++)
			{
				for(int i = 0; i < np; i++)
				{
					if (p2[j][0] == cross_child1[i][0])
					{		
						break;
					}											
					if (i == np-1)
					{
						for(int j1 = 0; j1 < np; j1++)
						{
							
							if (cross_child1[j1][0] == 0)
							{
								cross_child1[j1][0] = p2[j][0];
								//cout << cross_child1[j1][0] << '\n';
								break;
							}
						}	
					}
				}	
			}
			for(int j = 0; j < np; j++)
			{
				for(int i = 0; i < np; i++)
				{
					if (p1[j][0] == cross_child2[i][0])
					{		
						break;
					}											
					if (i == np-1)
					{
						for(int j1 = 0; j1 < np; j1++)
						{
							
							if (cross_child2[j1][0] == 0)
							{
								cross_child2[j1][0] = p1[j][0];
								//cout << cross_child2[j1][0] << '\n';
								break;
							}
						}	
					}
				}	
			}
			/*disc1 = 0.0;
			disc2 = 0.0;
			for(int m = 1; m < np; m++)
			{
				disc1 = disc1 + dist_master[cross_child1[m][0] - 1][cross_child1[m-1][0] - 1];	
				disc2 = disc2 + dist_master[cross_child2[m][0] - 1][cross_child2[m-1][0] - 1];
			}
			if (disc1 >= disc2)	
			{
				for(long m = 0; m < np; m++)
				{
					childf[m][0] = cross_child1[m][0];
				}
			}
			else
			{
				for(long m = 0; m < np; m++)
				{
					childf[m][0] = cross_child2[m][0];
				}
			}
			
			for(long i = 0; i < np; i++)
			{
				new_pop[i][paren_iter] = childf[i][0];
			}*/
			for(int i = 0; i < np; i++)
			{
				new_child[i][paren_iter] = cross_child1[i][0];
				new_child[i][paren_iter+1] = cross_child2[i][0];
			}
			paren_iter = paren_iter + 2;						
		}
	}
	/*for(int i = 0; i < np; i++)
	{
		for(int j = 0; j < popo; j++)
		{
			cout << new_child[i][j] << " ";
		}
		cout << '\n';
	}*/
	//cout << '\n';
	for(int j = 0; j < (2*par); j++)
	{
		dis[0][0] = 0.0;
		for(int m = 1; m < np; m++)
		{
		dis[0][0] = dis[0][0] + dist_master[new_child[m][j] - 1][new_child[m-1][j] - 1]	;
		//cout << dist_master[4][1];
		}
		dist_pop_child[j][0] = dis[0][0];
		dist_pop_child[j][1] = j+1;
		//cout << dist_pop_child[j][0];
	}
	//print distance array
	/*for(long j = 0; j < popo; j++)
	{
		for(long i = 0; i < 2; i++)
		{
			cout << dist_pop[j][i] << " ";
		}
		cout << '\n';
	}*/	
	//cout << '\n';
	//sort distance array
	float temp12 = 0;
	int temp22 = 0;
	for(int j = 0; j < (2*par); j++)
	{
		for(int i = 1; i < (2*par); i++)
		{	
			if (dist_pop_child[i][0] > dist_pop_child[i-1][0])
			{	
				temp12 = dist_pop_child[i-1][0];
				temp22 = dist_pop_child[i-1][1];
				dist_pop_child[i-1][0] = dist_pop_child[i][0];
				dist_pop_child[i-1][1] = dist_pop_child[i][1];
				dist_pop_child[i][0] = temp12;
				dist_pop_child[i][1] = temp22;				
			}
		}
	}
	//print sorted distance array
	/*for(int j = 0; j < (2*par); j++)
	{
		for(int i = 0; i < 2; i++)
		{
			cout << dist_pop_child[j][i] << " ";
		}
		cout << '\n';
	}*/
	int bas = 0;
	for(int j = 0; j < par; j++)
	{
		for(int i = 0; i < np; i++)
		{
			bas = dist_pop_child[j][1];
			//cout << bas << '\n';
			new_pop[i][j] = new_child[i][bas - 1];
		}
	}
	/*for(int i = 0; i < np; i++)
	{
		for(int j = 0; j < popo; j++)
		{
			cout << new_pop[i][j] << " ";
		}
		cout << '\n';
	}*/
	int bes = 0;
	for(int j = 0; j < popo - par; j++)
	{
		for(int i = 0; i < np; i++)
		{
			bes = dist_pop[j][1];
			new_pop[i][j + par] = pop_shuffle[i][bes-1];
		}
	}
	/*for(int i = 0; i < np; i++)
	{
		for(int j = 0; j < popo; j++)
		{
			cout << new_pop[i][j] << " ";
		}
		cout << '\n';
	}*/
	//mutate the population
	int ka = 0;
	int rnd1 = 0;
	int rnd2 = 0;
	for(int l1 = 0 ; l1 < mut ; l1++)
	{
		ka = rand()%popo;
		rnd1 = rand()%np;
		rnd2 = rand()%np;
		temp = new_pop[rnd1][ka];
		new_pop[rnd1][ka] = new_pop[rnd2][ka];
		new_pop[rnd2][ka] = temp;	
	}
	
	for(int j = 0; j < np; j++)
	{
		for(int i = 0; i < popo; i++)
		{
			pop_shuffle[j][i] = new_pop[j][i];
		}
	}
	/*for(long j = 0; j < np; j++)
	{
		for(long i = 0; i < popo; i++)
		{
			cout << new_pop[j][i] << "  ";
		}
		cout << '\n';
	}*/
	
	
cout << i << '\n';	
}
for(int i = 0; i < pip; i++)
	{
		//cout << score[i][0] << '\n';
		//cout << i+1 << '\n';
	}

ofstream myfile;
myfile.open ("TSPGA2_TSP2I1_max.csv");
for(int i = 0; i < pip; i++)
{
	myfile << score[i][0] << '\n';		
}
myfile.close();

ofstream myfile1;
myfile1.open ("TSPGA2_TSP2I1_max_path.csv");
for(int i = 0; i < np; i++)
{
	myfile1 << path[i][0] << '\n';		
}
myfile1.close();
system("pause");
return 0;	
}




