#include <stdio.h>


int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static int day_tab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

main()
{

  int year = 1998;
  int month = 10;
  int day = 23;

  int dayOfYear = day_of_year(year, month, day);

  printf("%d/%d/%d is the %dth day of %d\n", month, day, year, dayOfYear, year);

  int newMonth, newDay;

  month_day(year, dayOfYear, &newMonth, &newDay);

  printf("%dth day of %d is the date %d/%d/%d\n", dayOfYear, year, newMonth, newDay, year);

}


int day_of_year(int year, int month, int day)   /*  set day of year from month & day */
{
  int i, leap;
  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; i < month; i++)
    day += *(*(day_tab+leap)+i);
  return (day);
}

void month_day(int year, int yearday, int *pmonth, int *pday) /* set month, day from day of year */
{
  int i, leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; yearday > *(*(day_tab+leap)+i); i++)
    yearday -= *(*(day_tab+leap)+i);
  *pmonth = i;
  *pday = yearday;
}
