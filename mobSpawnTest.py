from random import randint
lista = []
iterations = 1
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
lugares_pos = {}
for elem in lista:
    if (elem not in lugares_pos):
        lugares_pos[elem] = 1
    else:
        lugares_pos[elem] += 1                     
print(lugares_pos)

for elem in lugares_pos:
    if (lugares_pos[elem] >= 3):
        cant+=1
print(cant)        