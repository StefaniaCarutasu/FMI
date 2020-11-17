data Fruct
    = Mar String Bool
    |Portocala String Int

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala "Tarocco" _) = True
ePortocalaDeSicilia (Portocala "Moro" _) = True
ePortocalaDeSicilia (Portocala "Sanguinello" _) = True
ePortocalaDeSicilia _ = False

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia l = sum [nr | (Portocala s nr) <- l, ePortocalaDeSicilia (Portocala s nr)]

nrMereViermi :: [Fruct] -> Int
nrMereViermi list = length [(Mar s b) | (Mar s b) <- list, b == True]