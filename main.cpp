#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int Length(char w[50])
{
    int length = 0;
    while (w[length] != '\0')
        length++;
    return(length);
};

int main()
{
    //input
    int total_columns, symbols;
    cout << "Number of columns = ";
    cin >> total_columns;
    cout << endl << "Width of columns = ";
    cin >> symbols;

    //check
    if ((total_columns == 0)||(symbols == 0))
    {
        cout << "Error. The number of columns or width = 0.";
        return(1);
    }

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    //check file existence
    if (!fin.is_open())
    {
        cout << "Error. Can't open the file.";
        return(1);
    }

    char word[1000];
    int column = 1;
    int limit = symbols;
    bool flag = false;

    while(!fin.eof())
    {
        if (!flag)
            fin >> word;

        //check word length
        if (Length(word) > symbols)
        {
            cout << "The word \""
            << word << "\" is longer than \""
            << limit
            << "\" symbols. Please, correct it and restart the program.";
            return(0);
        }

        if (Length(word) <= limit)
        {
            fout << word;
            flag = false;
            limit -= Length(word);

            //space after word
            if(limit > 0)
            {
                fout<<" ";
                limit--;
            }
        }
        else
        {
            //addition to the width of the column space, if the word does not fit
            for (int i = 1; i <= limit; i++)
            {
                 fout << " ";
            }
            limit = 0;
            flag = true;
        }

        //add a space between the columns or go on the new line
        if((limit == 0)&&(column <= total_columns))
        {
            if (column != total_columns)
            {
                fout << "          ";
                column++;
            }
            else
            {
                fout<<endl;
                column = 1;
            }
            limit = symbols;
        }
    }
    return(0);
}
