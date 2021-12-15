import os

seed = 0
while True:
    os.system(f".\straights.exe {seed} < all_comp.in > result.out")
    with open('result.out', 'r') as f:
        lines = f.read().splitlines()
        l1 = lines[-2]
        l2 = lines[-3]
        
        if str(l1).endswith('wins!') and str(l2).endswith('wins!'):
            print(seed)
            print(f"l1: {l1}")
            print(f"l2: {l2}")
            break

    seed += 1