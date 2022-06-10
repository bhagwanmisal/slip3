#include <stdio.h>
#include <string.h>
int main()
{
 int n;
 char s[]={"yashchavhan"};
 n=strlen(s);
 printf("String=%s\nLength of string=%d\n",s,n);
}
#include <stdio.h>
#include <stdlib.h>
int main()
{
 int *a,i,s=0,n;
 printf("Enter lim");
 scanf("%d",&n);
 a=(int *)calloc(n,sizeof(int));
 printf("enter elements\n"); 
 for(i=0;i<n;i++)
 {
 scanf("%d",a+i);
 }
 for(i=0;i<n;i++)
 {
 s=s+*(a+i);
 }
 printf("Sum=%d\nAverage=%d\n",s,s/n);
}
RDBMS
 create table hospital(h_no int primary key,h_name varchar(30),city varchar(20));
CREATE TABLE
slip3=# insert into hospital values(111,'city hospital','Nagar');
INSERT 0 1
slip3=# insert into hospital values(112,'Alpha hospital','Shrirampur');
INSERT 0 1
slip3=# select * from hospital;
 h_no | h_name | city 
------+----------------+------------
 111 | city hospital | Nagar
 112 | Alpha hospital | Shrirampur
slip3=# create table doctor(d_no int primary key,d_name varchar(30),specialization 
varchar(35),charges int,hosp_no int references hospital(h_no));
CREATE TABLE
 ^
slip3=# insert into doctor values(101,'Madhuri','Dentist',500,112);
INSERT 0 1
slip3=# insert into doctor values(102,'Darshan','Homiopathic',1000,111);
INSERT 0 1
slip3=# insert into doctor values(103,'Labade','Bones',100,112);
INSERT 0 1
slip3=# insert into doctor values(104,'Yenage','Eyes',200,111);
INSERT 0 1
slip3=# select * from doctor;
 d_no | d_name | specialization | charges | hosp_no 
------+---------+----------------+---------+---------
 101 | Madhuri | Dentist | 500 | 112
 102 | Darshan | Homiopathic | 1000 | 111
 103 | Labade | Bones | 100 | 112
 104 | Yenage | Eyes | 200 | 111
slip3=# create or replace function fun() returns trigger
slip3-# as
slip3-# $$
slip3$# begin
slip3$# if(new.charges<0)then
slip3$# raise exception'Charges should not be less than 0';
slip3$# end if;
slip3$# end;
slip3$# $$
slip3-# language plpgsql;
CREATE FUNCTION
slip3=# create trigger t1
slip3-# before insert or update on doctor
slip3-# for each row execute procedure fun();
CREATE TRIGGER
slip3=# insert into doctor values(105,'Joshi','Eyes',-1,111);
ERROR: Charges should not be less than 0
CONTEXT: PL/pgSQL function fun() line 4 at RAISE
slip3=# create or replace function fun1(d_name1 varchar(20)) returns void
slip3-# as
slip3-# $$
slip3$# declare
slip3$# ans hospital%rowtype;
slip3$# begin
slip3$# select * into ans from hospital,doctor where doctor.hosp_no=hospital.h_no
slip3$# AND d_name=d_name1;
slip3$# raise notice'Hospital no=%',ans.h_no;
slip3$# raise notice'Hospital name=%',ans.h_name;
slip3$# raise notice'City=%',ans.city;
slip3$# end;
slip3$# $$
slip3-# language plpgsql;
CREATE FUNCTION
slip3=# select fun1('Madhuri');
NOTICE: Hospital no=112
NOTICE: Hospital name=Alpha hospital
NOTICE: City=Shrirampur
slip3=# create or replace function fun(city_name varchar(20)) returns void
slip3-# as
slip3-# $$
slip3$# declare
slip3$# c1 cursor for select * from hospital where city=city_name;
slip3$# r1 hospital%rowtype;
slip3$# begin
slip3$# for r1 in c1
slip3$# loop
slip3$# raise notice'Hospital no=%',r1.h_no;
slip3$# raise notice'Hospital name=%',r1.h_name;
slip3$# raise notice'City=%',r1.city;
slip3$# end loop;
slip3$# end;
slip3$# $$
slip3-# language plpgsql;
CREATE FUNCTION
slip3=# select fun('Nagar');
NOTICE: Hospital no=111
NOTICE: Hospital name=city hospital
NOTICE: City=Nagar
