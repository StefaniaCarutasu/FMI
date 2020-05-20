'''
*Heap-arbore binar
    -complet (mai putin ultimul nivel)
    -v[0] e radacina si orice v[i] are ca fii v[2*i+1] si v[2*i+2]
    -tatal lui v[i] e v[(i-1)/2]
*Min-heap-val tatalui<val fiilor
*Adaugarea in heap: O(1)
*h~log(n)
'''
n=6; m=6
M=[[3,8,12,20,50,60],[6,10,15,22,55,62],[12,13,16,25,60,65],[18,20,22,30,65,78],[25,30,35,40,75,80],[]]
def matrix_search(M, val):
    if M[0][0]>val or M[n-1][n-1]<val:
        return(-1,-1)
    i=n-1
    j=0
    while i>=0 and j<m:
        if val==M[i][j]: return(i,j)
        elif val<M[i][j]: i-=1
        else: j-=-1
    return(-1,-1)
