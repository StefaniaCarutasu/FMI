#Media = integrala (-inf, +inf) xf(x) dx

median <- function (va)
{
  
  if(va@dens_prob@nr_variabile == 1)       #cazul variabila unidimensionala
  {
    x <- va@dens_prob@variabile[1]
    
    if(va@dens_prob@nr_intervale == 1)     #cazul o singura ramura
    {
      f <- va@dens_prob@legi[1]
      
      x <- va@dens_prob@variabile[1]
      
      minX <- va@dens_prob@intervale[1][1]
      maxX <- va@dens_prob@intervale[1][2]
      j <- integrate (abs(x) * f, lower = minX, upper = maxX, abs.tol = 0L)
      if (j$value != Inf)
      {
        i <- integrate (x * f, lower = minX, upper = maxX, abs.tol = 0L)
        return(i$value)
      }
      else
        return ("Nu exista media")
     
    }
    else                #cazul mai multe ramuri
    {
      integrala <- 0
      for(i in 1:va@dens_pron@nr_intervale)
      {
        f <- va@dens_prob@legi[i]
        
        x <- va@dens_prob@variabile[1]
        
        minX <- va@dens_prob@intervale[i][1]
        maxX <- va@dens_prob@intervale[i][2]
        j <- integrate (x * f, lower = minX, upper = maxX, abs.tol = 0L)
        if (j$value == Inf)
          return("Nu exista media")
        integrala <- integrala + (integrate (x * f, lower = minX, upper = maxX, abs.tol = 0L))$value
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
      j <- integral2(abs(x) * abs(y) * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = TRUE)
      if(j$value != Inf)
      {
        
          i <- integral2(x * y * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = TRUE)
          integrala <- unlist(i[1])[1]
          return(integrala)
      }
      else 
        return("Nu exista media")
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
        
        j <- integral2(abs(x) * abs(y) * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = TRUE)
        if (unlist(j[1])[1] == Inf)
          return("Nu exista media")
        integr <- integral2(x * y * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = TRUE)
        integrala <- integrala +  unlist(integr[1])[1]
      }
      
      return(integrala)
    }
    
  }
  
}