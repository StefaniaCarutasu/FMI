#Lucrul cu functii in R

f <- function()
{
  #optional return()
}

f1 <- function(x)
{
  2^x
}

f1(3)

#Sa se scrie o functie care afiseaza toate nr prime 
#mai mici decat un n dat

isPrim <- function(x)
{
  for(i in 2:ceiling(sqrt(x)))
  {
    if(x%%i == 0) return(F)
  }
  return(T)
}

isPrim(3)

f_prim <- function(x)
{
  for(i in 2:n)
  if(isPrim(i))
    print(i)
}

t<-f_prim(101)

integrate(f1,0,3)

7/log(2)

