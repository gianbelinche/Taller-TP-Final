from random import randint
lista = []
iterations = 50
enemies = 200
for i in range(enemies):
    print(i)
    x = 0
    y = 0
    for j in range(iterations):
        mov = randint(1,4)
        if mov == 1:
            x+=1
        if mov == 2:
            x-=1
        if mov == 3:
            y+=1
        if mov == 4:
            y-=1
    lista.append((x,y))

cant = 0
lista_copy = lista.copy()
lista_copy.pop(0)
for elem in lista:
    for elem2 in lista_copy:
        if elem == elem2:
            cant+=1
            lista_copy.remove(elem2)
            print("(x,y) = ",elem)
    if len(lista_copy) != 0:        
        lista_copy.pop(0)
print(cant)            
