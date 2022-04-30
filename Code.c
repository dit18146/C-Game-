#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int menu(void);
char wselection(void);					//waepon selection
void cselect(int *pt1, int *pt2, int m, int n);		//selection h for hummer,b for bomb
int pointsystem(int level,int cmb, char ch);		//point system calcualtion
int hammer(int x, int y, int pos1, int pos2, int m, int n, char **arr, char temp,int *cmb);
void bomb(int x, int y, int m, int n, char **arr);
void gravity(int m, int n, int colors, char **arr);	//gravity
/*void shift(int m, int n, int colors, char **arr);				//push	*/
void adding(int x, int y, int m, int n, char **arr);
void checkcolour(int x, int y, int m, int n, int *pt1, int *pt2, char **arr);



int main(void)
{
	int m, n;						//dimensions of array
	int colors;					//number of colors
	int x, y;						//coordinates of specified board element
	char  **str;					//array that contains the playing field
	char ch, px;					//ch for weapon selection, px for saving the contents of a cell
	int level, mselect;				//No. of level and Main Menu selection
	int i, j;						//used for 'for' loops
	int pos1, pos2;
	int cmb;						//combo
	int points;	
	int c;							//counter
	int k, l, temp1;	//shuffle variables
	char *pt1, *pt2;
	pt1 = &cmb;
	c = 0;
	points = 0;
	cmb = 0;
	srand(time(NULL));		//setting the seed
	level = 1;						//set level number as 1
	mselect = menu();				//Menu
	switch (mselect)
	{
	case 1:		//Play
	{
		do
		{
			printf("Give first dimension of the board\n");
			scanf("%d", &m);
			printf("Give second dimension of the board\n");
			scanf("%d", &n);
		} while ((m < 1 || m>16) && (n < 1 || n>16));
		do
		{
			printf("Give number of colors (2-9)\n");
			scanf("%d", &colors);
		} while (colors < 2 || colors>9);
		printf("\n\n");
		str = (char**)malloc(m * sizeof(char*));
		if (str == NULL)
		{
			printf("memory allocation failed\n");
			exit(1);
		}
		for (i = 0; i < m; i++)
		{
			str[i] = (char*)malloc(m * sizeof(char));
			if (str[i] == NULL)
			{
				printf("memory allocation failed\n");
				exit(1);
			}
		}
		
			for (i = 0; i < m; i++)					//Generating the board.
			{
				for (j = 0; j < n; j++)
					str[i][j] = 49 + rand() % colors;
			}
			printf("level %d\n\n", level);
			printf("   ");
			for (j = 0; j < n; j++)
				printf("%2d", j + 1);
			printf("\n");
			printf("   ");
			for (j = 0; j < n; j++)
				printf("--");
			printf("\n");
			for (i = 0; i < m; i++)
			{
				printf("%2d|", i + 1);
				for (j = 0; j < n; j++)
				{
					printf("%2c", str[i][j]);
				}
				printf("\n");
			}
			printf("\n\n");

		//Player commands
		do
		{
			while (1)
			{
				ch = wselection();
				printf("\n");
				if (ch == 'x')			//CODE FOR EXITING THE GAME
				{
					printf("Are you sure you want to exit? Type y/Y to continue. Type a different character to cancel.\n");
					while ((ch = getchar()) != '\n' && ch != EOF) {}
					while ((ch = getchar()) != '\n' && ch != EOF)
					{
						if (ch == 'y' || ch == 'Y')
						{
							printf("You have finished %d levels\nYour final score is %d points.\nThanks for playing!\nSee you next time!\n", level-1, points);
							for (i = 0; i < m; i++)
							{
								free(str[i]);
							}
							free(str);
							return 0;
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
			if (ch == 'b')		//bomb main algorithm
			{
				cselect(&x, &y,m,n);
				bomb(x, y, m, n, str);
				gravity(m, n, colors, str);
				points = pointsystem(level, cmb, ch);
				printf("  ");
				for (i = 0; i < m; i++)
					printf("%2d", i + 1);
				printf("\n");
				printf("  ");
				for (i = 0; i < m; i++)
					printf("--");
				printf("\n");
				for (i = 0; i < m; i++)
				{
					printf("%d|", i + 1);
					for (j = 0; j < n; j++)
					{
						printf("%2c", str[i][j]);
					}
					printf("\n");
				}
				printf("\n\n");
			}
		if (ch == 'a')		//bomb main algorithm
		{
			cselect(&x, &y, m, n);
			adding(x, y, m, n, str);
			gravity(m, n, colors, str);
			points = pointsystem(level, cmb, ch);
			printf("  ");
			for (i = 0; i < m; i++)
				printf("%2d", i + 1);
			printf("\n");
			printf("  ");
			for (i = 0; i < m; i++)
				printf("--");
			printf("\n");
			for (i = 0; i < m; i++)
			{
				printf("%d|", i + 1);
				for (j = 0; j < n; j++)
				{
					printf("%2c", str[i][j]);
				}
				printf("\n");
			}
			printf("\n\n");

		}
			
			
			if (ch == 'h')		//hammer main algorithm
			{
				cselect(&x, &y, m, n);
				char temp;
				temp = str[x][y];
				checkcolour(x, y, m, n, &pos1, &pos2, str);
				hammer(x, y, pos1, pos2, m, n, str, temp,&cmb);
				if (cmb == 1)
				{
					str[x][y] = temp;
					printf("cannot place a hammer in a single colour\n");
					cmb = 0;
				}
				gravity(m, n, colors, str);
				points = pointsystem(level, cmb, ch);
				printf("  ");
				for (i = 0; i < m; i++)
					printf("%2d", i + 1);
				printf("\n");
				printf("  ");
				for (i = 0; i < m; i++)
					printf("--");
				printf("\n");
				for (i = 0; i < m; i++)
				{
					printf("%d|", i + 1);
					for (j = 0; j < n; j++)
					{
						printf("%2c", str[i][j]);
					}
					printf("\n");
				}
				printf("\n\n");
			}
			printf("\n\n");
			for (i = 0; i < m; i++)
			{
				for (j= 0; j < n; j++)
				{
					if (str[i][j] == '.')
						c = ++c;
				}
			}
			if (c == m * n)		//level resetting
			{
				printf("level %d completed\n", level);
				level = level + 1;
				for (i = 0; i < m; i++)
				{
					free(str[i]);
				}
				free(str);
				m = m + 1;
				n = n + 1;
				str = (char**)malloc(m * sizeof(char*));
				if (str == NULL)
				{
					printf("memory allocation failed\n");
					exit(1);
				}
				for (i = 0; i < m; i++)
				{
					str[i] = (char*)malloc(m * sizeof(char));
					if (str[i] == NULL)
					{
						printf("memory allocation failed\n");
						exit(1);
					}
				}

				for (i = 0; i < m; i++)					//Regenerating the board.
				{
					for (j = 0; j < n; j++)
						str[i][j] = 49 + rand() % colors;
				}
				printf("level %d\n\n", level);
				printf("   ");
				for (j = 0; j < n; j++)
					printf("%2d", j + 1);
				printf("\n");
				printf("   ");
				for (j = 0; j < n; j++)
					printf("--");
				printf("\n");
				for (i = 0; i < m; i++)
				{
					printf("%2d|", i + 1);
					for (j = 0; j < n; j++)
					{
						printf("%2c", str[i][j]);
					}
					printf("\n");
				}
				printf("\n\n");
			}
		} while (1);
		
	}
	case 2:
	{
		return 0;
	}
	}
}


int menu(void)		//menu printing function
{
	int mselect;
	printf("\t|Welcome to the game|\n");
	printf("\t--------------------");
	printf("\n\n");
	printf("1.Play game\t 2.Exit\n\n");
	do {
		scanf("%d", &mselect);
	} while (mselect < 1 || mselect>2);
	printf("\n\n");
	return mselect;
}


char wselection(void) //weapon selection
{
	printf("Give wanted weapon choice (h, b, p, a) or type x to exit.\n");
	char ch;	//selection h for hammer, b for bomb, p for push, a for add, x for exit
	while ((ch = getchar()) != '\n' && ch != EOF) {}
	while ((ch = getchar()) != '\n' && ch != EOF)
	{

		if (ch == 'h')
			printf("hammer\n");
		else if (ch == 'b')
			printf("bomb\n");
		/*else if (ch == 'p')
			printf("push\n");*/
		else if (ch == 'a')
			printf("adding new colour element\n");
		else if (ch == 'x')
			printf("exit\n");
		else
		{
			printf("wrong input\n");
			while ((ch = getchar()) != '\n' && ch != EOF) {}
			continue;
		}
		return ch;

	}
}



void cselect(int *pt1, int *pt2, int m, int n)	//coordinate selection
{
	printf("give coordinates of wanted element seperated by space: ");

	scanf("%d ", pt1);
	scanf("%d", pt2);
	if (*pt1 > m || *pt2 > n || *pt1 < 0 || *pt2 < 0)
	{
		printf("wrong coordinate inputs please try again\n\n");
		printf("give coordinates of wanted element seperated by space: ");
		scanf("%d ", pt1);
		scanf("%d", pt2);
	}
	*pt1 = --*pt1;
	*pt2 = --*pt2;
	printf("\n");
	printf("selected element is placed at %d,%d\n", *pt1 + 1, *pt2 + 1);
}


int pointsystem(int level, int cmb , char ch)		//point calculation
{
	int points;
	int f;
	int temp;
	points = 0;
	int c;
	if (ch == 'h')
	{
		switch (cmb)
		{
		case 2:
		{
			points = 5;
			break;
		}
		case 3:
		{
			points = 15;
			break;
		}
		case 4:
		{
			points = 25;
			break;
		}
		case 5:
		{
			points = 50;
			break;
		}
		case 6:
		{
			points = 75;
			break;
		}
		case 7:
		{
			points = 100;
			break;
		}
		default:
		{
			points = 100;
			break;
		}
		}
	}
	else
	{
		points = 10;
	}
	printf("Got %d points!\n\n", points);
	return points;
}



void bomb(int x, int y, int m, int n, char **arr)		//bomb function
{
	if (x >= 1 && y >= 1 && x < m-1 && y < n-1)
	{
		arr[x][y] = '.';
		arr[x + 1][y] = '.';
		arr[x][y + 1] = '.';
		arr[x - 1][y] = '.';
		arr[x][y - 1] = '.';
		arr[x - 1][y - 1] = '.';
		arr[x + 1][y + 1] = '.';
		arr[x + 1][y - 1] = '.';
		arr[x - 1][y + 1] = '.';
	}
}



void gravity(int m, int n, int colors, char **arr)
{
	int i, j;
	char temp;
	int flag = 0;
	int k;
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m - 1; i++)
		{
			if ((arr[i][j] >= '1' && arr[i][j] < '1' + colors) && (arr[i + 1][j] == '.'))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			for (i = (m - 1); i > 0; i--)
			{
				for (k = m - 1; k >= 1; k--)
				{
					if ((arr[k - 1][j] >= '1' && arr[k - 1][j] < '1' + colors) && (arr[k][j] == '.'))
					{
						temp = arr[k - 1][j];
						arr[k - 1][j] = arr[k][j];
						arr[k][j] = temp;
					}
				}
			}
		}
	}
}

void adding(int x, int y, int m, int n, char **arr)		//add colour function
{

	char c;		//colour
	printf("give colour\n");
	while ((c = getchar()) != '\n' && c != EOF) {}
	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (c >= 48 && c <= 57)
		{
			if (arr[x][y] == '.')
				arr[x][y] = c;
		}
		else
			printf("wrong input\n");
	}

}


int hammer(int x, int y, int pos1, int pos2, int m, int n, char **arr, char temp,int *cmb)		//hammer function
{

	int f;
	
	




	// if (x,y is goal) return true 
	if (x == pos1 && y == pos2)
	{
		arr[x][y] = '.';
		return 1;
	}

	if (x >= 0 && x < m && y >= 0 && y < n && arr[x][y] == temp)
	{
		f = 1;
	}

	else
		f = 0;
	

	// Check if maze[x][y] is valid 
	if (f == 1)
	{
		// mark x,y as part of solution path 
		arr[x][y] = '.';
		*cmb = *cmb + 1;

		/* Move forward in x direction */
		if (hammer(x + 1, y, pos1, pos2, m, n, arr, temp,cmb) == 1)
		
			return 1;
	

		if (hammer(x - 1, y, pos1, pos2, m, n, arr, temp,cmb) == 1)

			return 1;

		/* If moving in x direction doesn't give solution then
			Move down in y direction  */
		if (hammer(x, y+1, pos1, pos2, m, n, arr, temp,cmb) == 1)

			return 1;
		

		if (hammer(x, y-1, pos1, pos2, m, n, arr, temp,cmb) == 1)

			return 1;
		/* If none of the above movements work then BACKTRACK:
			unmark x,y as part of solution path */
	}
	return 0;
}


void checkcolour(int x, int y, int m, int n, int *pt1, int *pt2, char **arr)
{
	int i, j;
	int pos1, pos2;
	pt1 = &pos1;
	pt2 = &pos2;
	if (x > 0 && x < m - 1 && y > 0 && y < n - 1)
	{
		if (arr[x + 1][y] == arr[x][y])
			x = x + 1;
		else if (arr[x - 1][y] == arr[x][y])
			x = x - 1;
		else if (arr[x][y + 1] == arr[x][y])
			y = y + 1;
		else if (arr[x][y - 1] == arr[x][y])
			y = y - 1;
		x = pos1;
		y = pos2;
	}
}

