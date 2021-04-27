#Dispersia = integrala (-inf, inf) x^2 * f(x) dx - (integrala (-inf, inf) x * f(x) dx) ^ 2

dispersion <- function(va)
{
  if(va@dens_prob@nr_variabile == 1)       #cazul variabila unidimensionala
  {
    x <- va@dens_prob@variabile[1]
    
    if(va@dens_prob@nr_intervale == 1)     #cazul o singura ramura
    {
      f <- va@dens_prob@legi[1]
      minX <- va@dens_prob@intervale[1][1]
      maxX <- va@dens_prob@intervale[1][2]
      
      int1 <- integrate (x ^ 2 * f, lower = minX, upper = maxX, abs.tol = 0L)
      int2 <- integrate (x * f, lower = minX, upper = maxX, abs.tol = 0L)
      disp <- int1$value - (int2$value) ^ 2
      
      return(disp)
      
    }
    else                #cazul mai multe ramuri
    {
     int1 <- 0
     int2 <- 0
     
      for(i in 1:va@dens_pron@nr_intervale)
      {
        f <- va@dens_prob@legi[i]
        minX <- va@dens_prob@intervale[i][1]
        maxX <- va@dens_prob@intervale[i][2]
        
        int1 <- int1 + (integrate (x ^ 2 * f, lower = minX, upper = maxX, abs.tol = 0L))$value
        int2 <- int2 + ((integrate (x * f, lower = minX, upper = maxX, abs.tol = 0L)$value) ^ 2
        
      }
     
      disp <- int1 - int2
      return(disp)
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
      
      minY <- va@dens_prob@intervale[i][3]
      maxY <- va@dens_prob@intervale[i][4]
      
      int1 <- integral2((x ^ 2) * (y ^ 2) * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = FALSE)
      int2 <- integral2(x * y * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = FALSE)
      disp <- (unlist(int1[1])[1] - ((unlist(int2[1])[1]) ^ 2
      
      return(disp)
    }
    else                #mai multe ramuri
    {
      int1 <- 0
      int2 <- 0
      
      for(i in 1:va@dens_pron@nr_intervale)
      {
        f <- va@dens_prob@legi[i]
        minX <- va@dens_prob@intervale[i][1]
        maxX <- va@dens_prob@intervale[i][2]
        
        minY <- va@dens_prob@intervale[i][3]
        maxY <- va@dens_prob@intervale[i][4]
        
        integr1 <- integral2((x ^ 2) * (y ^ 2) * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = FALSE)
        integr2 <- integral2(x * y * f, minX, maxX, minY, maxY, sector = FALSE, abs.tol = 0L, singular = FALSE, vectorized = FALSE)
        
        int1 <- int1 + unlist(integr1[1])[1]
        int2 <- int2 + (unlist(integr2[1])[1]) ^ 2
        
      }
      
      disp <- int1 - int2
      return(disp)
    }
    
  }
  
}
