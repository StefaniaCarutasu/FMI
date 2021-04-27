#Momente de ordin k = integrala (-inf, inf) x ^ k f(x) dx

kmoment <- function (va, ord)
{
  if(ord > 0 && ord <= 4)
  {
    if(va@dens_prob@nr_variabile == 1)       #cazul variabila unidimensionala
    {
      x <- va@dens_prob@variabile[1]
      
      if(va@dens_prob@nr_intervale == 1)     #cazul o singura ramura
      {
        
        f <- va@dens_prob@legi[1]
        minX <- va@dens_prob@intervale[1][1]
        maxX <- va@dens_prob@intervale[1][2]
        
        integrala <- integrate ((x ^ k) * f, lower = minX, upper = maxX, abs.tol = 0L)
        
        return(integrala$value)
        
      }
      else                #cazul mai multe ramuri
      {
        integrala <- 0
        
        for(i in 1:va@dens_pron@nr_intervale)
        {
          f <- va@dens_prob@legi[i]
          minX <- va@dens_prob@intervale[i][1]
          maxX <- va@dens_prob@intervale[i][2]
          
          integrala <- integrala + (integrate ((x ^ k) * f, lower = minX, upper = maxX, abs.tol = 0L))$value
        }
        
        return(integrala)
      }
    }
    else            #cazul variabila bidimensionala
    {
      x <- va@dens_prob@variabile[1]
      y <- va@dens_prob@variabile[2]
      
      if(va@dens_prob@nr_intervale == 1)          #o singura ramura
      {
        f <- va@dens_prob@legi[1]
        minX <- va@dens_prob@intervale[1][1]
        maxX <- va@dens_prob@intervale[1][2]
        
        minY <- va@dens_prob@intervale[1][3]
        maxY <- va@dens_prob@intervale[1][4]
        
        integr <- integral2((x ^ k) * (y ^ k) * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = FALSE)
        integrala <- unlist(integr[1])[1]
        
        return(integrala)
      }
      else                #mai multe ramuri
      {
        integrala <- 0
        for(i in 1:va@dens_pron@nr_intervale)
        {
          f <- va@dens_prob@legi[i]
          minX <- va@dens_prob@intervale[i][1]
          maxX <- va@dens_prob@intervale[i][2]
          
          minY <- va@dens_prob@intervale[i][3]
          maxY <- va@dens_prob@intervale[i][4]
          
          integr <-  integral2((x ^ k) * (y ^ k) * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = FALSE)
          integrala <- integrala + unlist(integr[1])[1]
        }
        
        return(integrala)
      }
      
    }
  }
  else
  {
    if (ord <= 0)
      return("Ordinul trebuie sa fie un numar pozitiv")
    else
      return("Ordinul trebuie sa fie un numar pozitiv mai mic decat 4")
  }
}