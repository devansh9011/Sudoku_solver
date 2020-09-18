#include<iostream>

using namespace std;

class sudoku 
{	
private:
	int grid[9][9];
public:
	void input();
	bool row_check(int, int);
	bool column_check(int, int);
	bool box_check(int, int, int);
	bool is_valid_place(int, int, int);
    bool is_solved(int&, int&);
	bool sudoku_solver();
    void print_sudoku();
};

void sudoku::input()                        //taking the input
{
	cout<<"\nEnter the sudoku grid (empty places should be marked as zero)\n\n";
	for(int i=0 ; i<9 ; i++)
		for(int j=0 ; j<9 ; j++)
			cin>>grid[i][j];
}

bool sudoku::row_check(int row, int val) 	  //checking if the number is present in the row
{      
    for(int j=0 ; j<9 ; j++)
        if(grid[row][j]==val) 
            return false;
    return true;
}

bool sudoku::column_check(int col, int val)     //checking if the number is present in the column
{    
    for(int i=0 ; i<9 ; i++)
        if(grid[i][col]==val) 
            return false;
    return true;
}

bool sudoku::box_check(int startRow, int startCol, int val)  //check if the number is present in the 3x3 box
{    
    for(int i=0 ; i<3 ; i++)
        for(int j=0 ; j<3 ; j++)
            if(grid[i+startRow][j+startCol]==val) 
                return false;
    return true;
}

bool sudoku::is_valid_place(int row, int col, int val)		//checking if the number can be assinged to the given row and column or not
{    
    return (row_check(row,val) && column_check(col,val) && box_check(row/3*3, col/3*3, val)); 
}


bool sudoku::is_solved(int &i, int &j)      //function to check whether sudoku is solved or not, if not then gives the position which is not found yet
{       
    for(i=0 ; i<9 ; i++)
        for(j=0 ; j<9 ; j++)
            if(!grid[i][j])                 //if empty place i.e. 0
                return false;   
    return true;
}

bool sudoku::sudoku_solver() 			    //solve the sudoku using backtracking
{   
    int row,col;
    if(is_solved(row,col))                  //if the sudoku is solved
        return true;   
    for(int i=1 ; i<=9 ; i++) 
    {
        if(is_valid_place(row,col,i)) 
        {
            grid[row][col] = i;             //insert the number
            if(sudoku_solver())             //recursively checking whether the assignment yeilds a solution or not
                return true;
            grid[row][col] = 0;             //return to previous state or undo the change for backtracking
        }
    }
    return false;
}


void sudoku::print_sudoku()                 //printing the sudoku solution
{        
    cout<<"\nSolution is \n";
    cout<<"\n-------------------------\n";
    for (int i=0 ; i<9 ; i++) 
    {
        for (int j=0 ; j<9 ; j++) 
        {   
            if(j%3==0)
                cout << "| ";
            cout << grid[i][j] <<" ";
        }
        if(i%3==2) 
            cout << "|\n-------------------------\n";
        else
            cout <<"|\n";
   }
}

int main()
{
    sudoku sudo;        					
    sudo.input();                        
    if(sudo.sudoku_solver())				
    	sudo.print_sudoku();
    else 
        cout<<"No answer exists!!!";

    return 0;
}
