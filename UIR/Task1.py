"""
Суть задачи заключается в том, что нужно реализовать алгоритм поиска простых чисел 
"""
simple_nums = []
N = 150
number_bool_line = [True] * N

for i in range(2, int(N**0.5)+1):
    if number_bool_line[i]:
        for j in range(i*i, N, i):
            number_bool_line[j] = False


for i in range(2, N):
    if number_bool_line[i]:
        simple_nums.append(i)

print(simple_nums)