v = int(input())

print( max(min(255, v+16)-32, 0)+16 )
print( min(max(0, (v+16)-32), 255)+16 )