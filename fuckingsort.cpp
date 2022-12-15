#include <iostream>
using namespace std;

struct vitek
{
  int LK;           
  struct vitek *halyava;  
  struct vitek *fucker;
};

void print(vitek *mark)
{
  if (mark != NULL) {      
    print(mark->halyava); 
    cout << mark->LK << " ";
    print(mark->fucker);
  }
}

struct vitek * add_semen(int x, vitek *mark) {
  if (mark == NULL)     
  {
    mark = new vitek; 
    mark->LK = x;  
    mark->halyava = NULL;
    mark->fucker = NULL;
  }

  else   
    if (x < mark->LK)  
      mark->halyava = add_semen(x, mark->halyava); 

    else 
      mark->fucker = add_semen(x, mark->fucker);
    return(mark);
}

void freemem(vitek *mark)
{
  if (mark != NULL)  
  {
    freemem(mark->halyava);  
    freemem(mark->fucker); 
    delete mark;     
  }
}

int main()
{
  struct vitek *arr = 0; 
  int current;    

  for (int i = 0; i< 8; i++)     //enter 8 marks
  {
    cout << i + 1 << ": ";
    cin >> current;
    arr = add_semen(current, arr); 
  }

  print(arr);  
  freemem(arr);   
  cin.get();  cin.get();

  return 0;
}