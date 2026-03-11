import sys
letters = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЫЭЮЯ"

def solve():
    s = sys.stdin.readline().rstrip('\n\r')
    if not s:
        return

    n = sum(1 for c in s if c != ' ')
    a = letters.find(s[0]) + 1

    b = 0
    space_index = s.find(' ')
    if space_index != -1 and space_index + 1 < len(s):
        char_after_space = s[space_index + 1]
        b = letters.find(char_after_space) + 1

    print(f"{n}{a}{b}")

if __name__ == "__main__":
    solve()