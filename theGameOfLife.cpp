//Munem Hashmi
//The Game of Life
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

const int size=20;									//Global Initialization of Grid Size									
void start();										//Definition of Start Function
void instructions();									//Definition of Instructions Displaying Function
bool reading_file(string,bool [][size]);						//Definition of Alive Cells Coordinates Reading Function
int  generation_read(int, string);							//Definition of Generation Reading Function
int  cellsnum_read(int, string);							//Definition of Alive Cells Reading Function
void display(bool [][size]);								//Definition of Grid Displaying Function
int  secarr(bool [][size], int [][2],int);						//Definition of Sec-Array Finding Function
void disp_secarr(int,int [][2]);							//Definition of Sec-Array Displaying Function
int  neiarr(bool [][size], int [][2], bool [][size],int);				//Definition of Nei-Array Finding Function
void disp_neiarr(int,int [][2]);							//Definition of Nei-Array Displaying Function
void comparison(bool [][size], bool[][size]);						//Definition of Function
void rules(bool [][size],bool [][size]);						//Definition of Rules Applying Function
void file_writing(int,int,int [][2]);							//Definition of File Writing Function

//*******************************************************************************************************************************/
//							Main Function								/
//*****************************************************************************************************************************/
				
int main()
{
	start();									//Calling Start Function										
	return 0;
}

//*******************************************************************************************************************************/
//							Start Function								/
// 					THIS FUNCTION IS RESPONSIBLE FOR GAME PROCESSING				       /
//****************************************************************************************************************************/

void start()
{

	int sec_arr[100][2];								//Sec-Array declaration
	int nei_arr[300][2];								//Nei-Array declaration
	bool grid[size][size]={};								
	bool copy[size][size]={};
	bool fixduplication[size][size]={};
	int generation;									//Generation variable declaration
	int cellsnum;									//Alive cells variable declaration
	int deadcells;									//Dead Neighboring cells variable declaration
	int gcount=0;									//Generation count variable initialization
	string filename;								//filename variable declarartion


	instructions();									//Calling instructions displaying function


	cout << "ENTER THE NAME OF FILE TO READ FROM: "<<endl;				//File Name Prompt
	cin  >> filename;


	reading_file(filename,grid);							//Calling file reading function
							
	while (reading_file(filename,grid))						//Validation for incorrect file name loop continues until correct input is entered
	{

		cout << "FILE NOT FOUND."<<endl;
		cout<< "ENTER THE FILE NAME AGAIN"<<endl;
		cin>>filename;
		reading_file(filename,grid);						//Calling file reading function incase of wrong file name

	}

	generation=generation_read(generation,filename);				//generation initialization with generation reading function
	cellsnum  =cellsnum_read(cellsnum,filename);					//alivecells initialization with alivecells reading function
	
	while (gcount<=generation)							//Loop to display game simulation until generation is reached
	{

		cout<<endl;								//Newlines
		cout<<endl;
		cout<<endl;

		cout<< "DISPLAYING GENERATION NUMBER		:"<<gcount<<endl;	//Displaying Generation Number
		cout<<endl;
		cout<<endl;								//Newlines

		display(grid);								//Calling Display Function
		secarr(grid, sec_arr,cellsnum);						//Calling sec-array finding number
		cellsnum=secarr(grid, sec_arr,cellsnum);				//Alive cells after each generation				
		disp_secarr(cellsnum,sec_arr);						//Displaying Sec-array function

		neiarr(grid, nei_arr, fixduplication,deadcells);			//Calling nei-array finding function
		deadcells=neiarr(grid, nei_arr, fixduplication,deadcells);		//Dead neighboring cells
		disp_neiarr(deadcells, nei_arr);					//Nei-Array Displaying
		comparison(grid,copy);							//
		rules(grid,copy);							//Calling Games rules applying function
		file_writing(generation,cellsnum,sec_arr);				//Calling File writing Function

		gcount++;								//Generation count increment

	}

}

//*******************************************************************************************************************************/
//							Instructions Function							/
// 					THIS FUNCTION IS RESPONSIBLE FOR DISPLAYING GAME INSTRUCTIONS			       /
//****************************************************************************************************************************/

void instructions()
{

	cout<< "			THE GAME OF LIFE	"<<endl;
	cout<< "In this game Cells are arranged in a two-dimensional Grid"<<endl;
	cout<< "1. Two possible states for each cell"<<endl;
	cout<< "a) Live"<<endl;
	cout<< "b) Dead"<<endl;
	cout<< "2. States can change"<<endl;
	cout<< "a) Living cell can die (death)."<<endl;
	cout<< "b) Dead cell can become alive (birth)."<<endl;
	cout<< "3. Simple set of rules specifying"<<endl;
	cout<< "a) Death (overcrowding OR underpopulation)."<<endl;
	cout<< "b) Birth (reproduction)."<<endl;
	cout<<endl;
	cout<< "		THE RULES OF THE GAME ARE AS FOLLOWS"<<endl;
	cout<< "Rule: 1"<<endl;
	cout<< "If the cell is dead:"<<endl;
	cout<< "Birth: if exactly three of its neighbors are alive, the cell will become alive at the next step."<<endl;
	cout<< "If the cell is already alive:"<<endl;
	cout<< "Rule: 2"<<endl;
	cout<< "Survival: if the cell has two or three live neighbors, the cell remains alive."<<endl;
	cout<< "Otherwise, the cell will die:"<<endl;
	cout<< "Rule: 3"<<endl;
	cout<< "Death by loneliness: if the cell has only zero or one alive neighbor, the cell will become dead at the next step."<<endl;
	cout<< "Rule:4"<<endl;
	cout<< "Death by overcrowding: if the cell is alive and has more than three alive neighbors, the cell also dies."<<endl;
	cout<<endl;

	
}

//*******************************************************************************************************************************/
//							File Reading Function							/
// 				THIS FUNCTION IS RESPONSIBLE FOR READING ALIVE CELLS COORDINATES FROM FILE	               /
//****************************************************************************************************************************/

bool reading_file(string filename,bool grid[][size])
{

	int generation;
	int cellsnum;
	int x1,y1;						//reading alive cells coordinates 
	ifstream readfile(filename);
	if (!readfile)
	{

		return true;

	}
	if (readfile.is_open())
	{

		readfile>>generation;
		readfile>>cellsnum;
		for (int i=0;i<cellsnum;i++)
		{

			readfile>>x1>>y1;
			grid[x1][y1]=true;

		}

	}
	readfile.close();
	return false;
}

//*******************************************************************************************************************************/
//							Generation Reading Function						/
// 					THIS FUNCTION IS RESPONSIBLE FOR READING GENERATIONS FROM FILE	                       /
//****************************************************************************************************************************/

int generation_read(int generation, string filename)
{

	ifstream readfile(filename);				//reading generation from file sending it into start function
	if (readfile.is_open())
	{

		readfile>>generation;
	}
		readfile.close();
	return generation;

}

//*******************************************************************************************************************************/
//							Alivecells Reading Function						/
// 					THIS FUNCTION IS RESPONSIBLE FOR READING ALIVECELLS FROM FILE	                       /
//****************************************************************************************************************************/

int cellsnum_read(int cellsnum, string filename)
{

	int generation;
	ifstream readfile(filename);				//reading alive cells number sending in to start function
	if (readfile.is_open())
	{

		readfile>>generation;
		readfile>>cellsnum;

	}
	readfile.close();
	return cellsnum;;
	
}

//*******************************************************************************************************************************/
//							Grid Displaying Function						/
// 					THIS FUNCTION IS RESPONSIBLE FOR DISPLAYING GRID	                       	       /
//****************************************************************************************************************************/

void display(bool grid[][size])
{
	
	
	for(int j = 0; j < size; j++)					//Displaying grid
	{

		for(int k = 0; k < size; k++)
		{	

			if(grid[j][k] == true)
			{

				cout << " 0 ";
				
			}

			else
			{

				cout << " . ";

			}

		}

	


	cout<<endl;

	}
	cout<<endl;

	
}

//*******************************************************************************************************************************/
//							Sec-Array Finding Function						/
// 					THIS FUNCTION IS RESPONSIBLE FOR FINDING SEC-ARRAY                                     /
//****************************************************************************************************************************/

int secarr(bool grid[][size], int sec_arr[][2],int cellsnum)
{
	
	int i=0;

	for(int j = 0; j < size; j++)					//nested loop to find secondary array
	{

		for(int k = 0; k < size; k++)
		{
	
			if(grid[j][k] == true)
			{

				sec_arr[i][0]=j;
				sec_arr[i][1]=k;
				i=i+1;
						
			}

		}

	}
	cellsnum=i;
	return cellsnum;
	
		
}

//*******************************************************************************************************************************/
//							Sec-Array Displaying Function						/
// 						THIS FUNCTION IS RESPONSIBLE FOR DISPLAYING SEC-ARRAY                          /
//****************************************************************************************************************************/

void disp_secarr(int cellsnum,int sec_arr[][2])
{

	cout<< "DISPLAYING NUMBER OF ALIVE CELLS"<<endl;
	cout<<cellsnum<<endl;
	cout<< "DISPLAYING SECONDARY ARRAY"<<endl;

	for(int j = 0; j <cellsnum; j++)				//nested loop to display nei-array
	{

		for(int k = 0; k <2; k++)
		{
	
			cout<<sec_arr[j][k];
			cout<<",";

		}
		cout<<" ";

	}
	cout<<endl;
}

//*******************************************************************************************************************************/
//							Nei-Array Finding Function						/
// 					THIS FUNCTION IS RESPONSIBLE FOR FINDING Nei-ARRAY                                     /
//****************************************************************************************************************************/

int neiarr(bool grid[][size], int nei_arr[][2],bool fixduplication[][size],int deadcells)
{
	
	int count=0;

	for(int j = 0; j < size; j++)					//loop to check neighbors and store in nei-array
	{

		for(int k = 0; k < size; k++)
		{	

			if(grid[j][k] == true)
			{

				if (fixduplication [j-1][k-1]!=true)
				{

					if (grid [j-1][k-1]!=true)
					{

						nei_arr[count][0]=j-1;
						nei_arr[count][1]=k-1;
						count=count+1;
						fixduplication [j-1][k-1]=true;

					}
	
				}

				if (fixduplication [j][k-1]!=true)
				{

					if (grid [j][k-1]!=true)
					{

						nei_arr[count][0]=j;
						nei_arr[count][1]=k-1;
						count=count+1;
						fixduplication [j][k-1]=true;

					}

				}

				if (fixduplication [j+1][k-1]!=true)
				{

					if (grid [j+1][k-1]!=true)
					{

						nei_arr[count][0]=j+1;
						nei_arr[count][1]=k-1;
						count=count+1;
						fixduplication [j+1][k-1]=true;

					}

				}

				if (fixduplication [j-1][k]!=true)
				{

					if (grid [j-1][k]!=true)
					{

						nei_arr[count][0]=j-1;
						nei_arr[count][1]=k;
						count=count+1;
						fixduplication [j-1][k]=true;

					}

				}

				if (fixduplication [j+1][k]!=true)
				{
					if (grid [j+1][k]!=true)
					{

						nei_arr[count][0]=j+1;
						nei_arr[count][1]=k;
						count=count+1;
						fixduplication [j+1][k]=true;
		
					}

				}

				if (fixduplication [j-1][k+1]!=true)
				{

					if (grid [j-1][k+1]!=true)
					{

						nei_arr[count][0]=j-1;
						nei_arr[count][1]=k+1;
						count=count+1;
						fixduplication [j-1][k+1]=true;
		
					}
				}

				if (fixduplication [j][k+1]!=true)
				{

					if (grid [j][k+1]!=true)
					{
						nei_arr[count][0]=j;
						nei_arr[count][1]=k+1;
						count=count+1;
						fixduplication [j][k+1]=true;				
					}
				}

				if (fixduplication [j+1][k+1]!=true)
				{

					if (grid [j+1][k+1]!=true)
					{
						nei_arr[count][0]=j+1;
						nei_arr[count][1]=k+1;
						count=count+1;
						fixduplication [j+1][k+1]=true;		
					}

				}
					
			}

		}

	}

	deadcells=count;

	for (int m=0;m<size;m++)				//recreating array to its initial form							
	{

		for (int n=0;n<size;n++)
		{

			fixduplication[m][n]=false;

		}

	}
	return deadcells;
	
}

//*******************************************************************************************************************************/
//							Sec-Array Displaying Function						/
// 						THIS FUNCTION IS RESPONSIBLE FOR DISPLAYING SEC-ARRAY                          /
//****************************************************************************************************************************/

void disp_neiarr(int deadcells,int nei_arr[][2])
{

	int g=2;
	cout<< "DISPLAYING NUMBER OF DEAD NEIGHBORS"<<endl;
	cout<<deadcells<<endl;
	cout<< "DISPLAYING NEIGHBORHOOD"<<endl;

	for(int j = 0; j <deadcells; j++)				//nested loop to nei-array display array
	{

		for(int k = 0; k <g; k++)
		{	
			cout<<nei_arr[j][k];
			cout<<",";
		}
		cout<< " ";

	}
	cout<<endl;
	
}

//*******************************************************************************************************************************/
//							Comparison Function							/
// 					THIS FUNCTION IS RESPONSIBLE FOR COMPARISON                                 		/
//****************************************************************************************************************************/

void comparison(bool grid[][size],bool copy[][size])
{
	for(int a =0; a < size; a++)
	{

		for(int b = 0; b < size; b++)
		{

			copy[a][b] = grid[a][b];					

		}

	}

}

//*******************************************************************************************************************************/
//							Game Rules Applying Function						/
// 						THIS FUNCTION IS RESPONSIBLE APPLYING GAME RULES                               /
//****************************************************************************************************************************/

void rules(bool grid[][size],bool copy[][size])
{
	for(int i = 1; i < size-1; i++)
	{
		for(int j = 1; j < size-1; j++)
		{
			int live_nei= 0;

			for(int k = -1; k < 2; k++)
			{
				for(int l = -1; l < 2; l++)
				{
					if(!(k == 0 && l == 0))
					{
						if(copy[i+k][j+l]==true)
						{
							live_nei+=1;				//Live neighbor counting to assess birth or death of cells
						}
					}
				}
			}

			if(live_nei < 2)
			{
				grid[i][j] = false;						//death of cell by lonliness
			}

			else if(live_nei == 3)
			{
				grid[i][j] = true;						//birth of cells
			}

			else if(live_nei > 3)
			{
				grid[i][j] = false;						//death of cells by overcrowding
			}
		}
	}
}

//*******************************************************************************************************************************/
//							File Writing Function							/
// 						THIS FUNCTION IS RESPONSIBLE FOR FILE WRITING                         		/
//****************************************************************************************************************************/

void file_writing(int generation,int cellsnum,int sec_arr[][2])
{

	ofstream outputFile;								//Complete File Writing
	outputFile.open("output.txt",ios :: out);
	outputFile<<generation;
	outputFile<<"\n";
	outputFile<<cellsnum;
	outputFile<<"\n";

	for (int m=0;m<cellsnum;m++)							//Nested loop to write file
	{

		for (int n=0;n<2;n++)
		{

			outputFile<<sec_arr[m][n]<<" ";

		}
		outputFile<<"\n";

	}

	outputFile.close();
	
}











