#include <stdio.h>


struct date {
  int day;
  int month;
  int year;
  int yearday;
  char mon_name[4];
};

int day_of_year(struct date *);
void month_day(struct date *);

static int day_tab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

main()
{

  int year = 1998;
  int month = 10;
  int day = 23;
  
  struct date d = {day, month, year, 0, ""};

  int dayOfYear = day_of_year(&d);
  d.yearday = dayOfYear;

  printf("%d/%d/%d is the %dth day of %d\n", d.month, d.day, d.year, d.yearday, d.year);

  d.month = -1;
  d.day = -1;
  
  month_day(&d);

  printf("%dth day of %d is the date %d/%d/%d\n", d.yearday, d.year, d.month, d.day, d.year);

}


int day_of_year(struct date *pd)   /*  set day of year from month & day */
{
  int i, day, leap;
  
  day = pd->day;
  leap = pd->year % 4 == 0 && pd->year % 100 != 0 || pd->year % 400 == 0;
  for (i = 1; i < pd->month; i++)
    day += day_tab[leap][i];
  return (day);
}

void month_day(struct date *pd) /* set month, day from day of year */
{
  int i, leap;

  leap = pd->year % 4 == 0 && pd->year % 100 != 0 || pd->year % 400 == 0;
  pd->day = pd->yearday;
  for (i = 1; pd->day > day_tab[leap][i]; i++)
    pd->day -= day_tab[leap][i];
  pd->month = i;
}
