set springks 0
set springkd 1

system partSys dim 58
system partSys particle 0 10 0 1 0 0 0 0
system partSys particle 1 10 0.175 1 0.175 0 0 0
system partSys particle 2 10 1.40 1 1.39 0 0 0
system partSys particle 3 10 2.62 1 2.59 0 0 0
system partSys particle 4 10 3.84 1 3.75 0 0 0
system partSys particle 5 10 5.06 1 4.85 0 0 0
system partSys particle 6 10 6.28 1 5.88 0 0 0
system partSys particle 7 10 7.50 1 6.82 0 0 0
system partSys particle 8 10 8.73 1 7.66 0 0 0
system partSys particle 9 10 9.95 1 8.39 0 0 0
system partSys particle 10 10 11.2 1 8.99 0 0 0
system partSys particle 11 10 12.4 1 9.46 0 0 0
system partSys particle 12 10 13.6 1 9.78 0 0 0
system partSys particle 13 10 14.8 1 9.96 0 0 0
system partSys particle 14 10 16.1 1 10.0 0 0 0
system partSys particle 15 10 17.3 1 9.88 0 0 0
system partSys particle 16 10 18.5 1 9.61 0 0 0
system partSys particle 17 10 19.7 1 9.21 0 0 0
system partSys particle 18 10 20.9 1 8.66 0 0 0
system partSys particle 19 10 22.2 1 7.99 0 0 0
system partSys particle 20 10 23.4 1 7.19 0 0 0
system partSys particle 21 10 24.6 1 6.29 0 0 0
system partSys particle 22 10 25.8 1 5.30 0 0 0
system partSys particle 23 10 27.1 1 4.22 0 0 0
system partSys particle 24 10 28.3 1 3.09 0 0 0
system partSys particle 25 10 29.5 1 1.91 0 0 0
system partSys particle 26 10 30.7 1 0.698 0 0 0
system partSys particle 27 10 31.9 1 -0.523 0 0 0
system partSys particle 28 10 33.2 1 -1.74 0 0 0
system partSys particle 29 10 0 8 0 0 0 0
system partSys particle 30 10 0.175 8 0.175 0 0 0
system partSys particle 31 10 1.40 8 1.39 0 0 0
system partSys particle 32 10 2.62 8 2.59 0 0 0
system partSys particle 33 10 3.84 8 3.75 0 0 0
system partSys particle 34 10 5.06 8 4.85 0 0 0
system partSys particle 35 10 6.28 8 5.88 0 0 0
system partSys particle 36 10 7.50 8 6.82 0 0 0
system partSys particle 37 10 8.73 8 7.66 0 0 0
system partSys particle 38 10 9.95 8 8.39 0 0 0
system partSys particle 39 10 11.2 8 8.99 0 0 0
system partSys particle 40 10 12.4 8 9.46 0 0 0
system partSys particle 41 10 13.6 8 9.78 0 0 0
system partSys particle 42 10 14.8 8 9.96 0 0 0
system partSys particle 43 10 16.1 8 10.0 0 0 0
system partSys particle 44 10 17.3 8 9.88 0 0 0
system partSys particle 45 10 18.5 8 9.61 0 0 0
system partSys particle 46 10 19.7 8 9.21 0 0 0
system partSys particle 47 10 20.9 8 8.66 0 0 0
system partSys particle 48 10 22.2 8 7.99 0 0 0
system partSys particle 49 10 23.4 8 7.19 0 0 0
system partSys particle 50 10 24.6 8 6.29 0 0 0
system partSys particle 51 10 25.8 8 5.30 0 0 0
system partSys particle 52 10 27.1 8 4.22 0 0 0
system partSys particle 53 10 28.3 8 3.09 0 0 0
system partSys particle 54 10 29.5 8 1.91 0 0 0
system partSys particle 55 10 30.7 8 0.698 0 0 0
system partSys particle 56 10 31.9 8 -0.523 0 0 0
system partSys particle 57 10 33.2 8 -1.74 0 0 0

simulator partSim link partSys 113
set strength 0.1
simulator partSim spring 0 1 $springks $springkd $strength
simulator partSim spring 1 2 $springks $springkd $strength
simulator partSim spring 2 3 $springks $springkd $strength
simulator partSim spring 3 4 $springks $springkd $strength
simulator partSim spring 4 5 $springks $springkd $strength
simulator partSim spring 5 6 $springks $springkd $strength
simulator partSim spring 6 7 $springks $springkd $strength
simulator partSim spring 7 8 $springks $springkd $strength
simulator partSim spring 8 9 $springks $springkd $strength
simulator partSim spring 9 10 $springks $springkd $strength
simulator partSim spring 10 11 $springks $springkd $strength
simulator partSim spring 11 12 $springks $springkd $strength
simulator partSim spring 12 13 $springks $springkd $strength
simulator partSim spring 13 14 $springks $springkd $strength
simulator partSim spring 14 15 $springks $springkd $strength
simulator partSim spring 15 16 $springks $springkd $strength
simulator partSim spring 16 17 $springks $springkd $strength
simulator partSim spring 17 18 $springks $springkd $strength
simulator partSim spring 18 19 $springks $springkd $strength
simulator partSim spring 19 20 $springks $springkd $strength
simulator partSim spring 20 21 $springks $springkd $strength
simulator partSim spring 21 22 $springks $springkd $strength
simulator partSim spring 22 23 $springks $springkd $strength
simulator partSim spring 23 24 $springks $springkd $strength
simulator partSim spring 24 25 $springks $springkd $strength
simulator partSim spring 25 26 $springks $springkd $strength
simulator partSim spring 26 27 $springks $springkd $strength
simulator partSim spring 27 28 $springks $springkd $strength


set springks 0
simulator partSim spring 0 28 $springks $springkd 11
simulator partSim spring 1 27 $springks $springkd 10
simulator partSim spring 2 26 $springks $springkd 9
simulator partSim spring 3 25 $springks $springkd 8
simulator partSim spring 4 24 $springks $springkd 7
simulator partSim spring 5 23 $springks $springkd 6
simulator partSim spring 6 22 $springks $springkd 5
simulator partSim spring 7 21 $springks $springkd 4
simulator partSim spring 8 20 $springks $springkd 3
simulator partSim spring 9 19 $springks $springkd 2
simulator partSim spring 10 18 $springks $springkd 1
simulator partSim spring 11 17 $springks $springkd 0.5
simulator partSim spring 12 16 $springks $springkd 0.25
simulator partSim spring 13 15 $springks $springkd 0.1

simulator partSim spring 29 57 $springks $springkd 9
simulator partSim spring 30 56 $springks $springkd 8
simulator partSim spring 31 55 $springks $springkd 7
simulator partSim spring 32 54 $springks $springkd 6
simulator partSim spring 33 53 $springks $springkd 5
simulator partSim spring 34 52 $springks $springkd 4
simulator partSim spring 35 51 $springks $springkd 3
simulator partSim spring 36 50 $springks $springkd 2
simulator partSim spring 37 49 $springks $springkd 1
simulator partSim spring 38 48 $springks $springkd 0.5
simulator partSim spring 39 47 $springks $springkd 0.25
simulator partSim spring 40 46 $springks $springkd 0.1
simulator partSim spring 41 45 $springks $springkd 0.1
simulator partSim spring 42 44 $springks $springkd 0.1

simulator partSim spring 29 30 $springks $springkd $strength
simulator partSim spring 30 31 $springks $springkd $strength
simulator partSim spring 31 32 $springks $springkd $strength
simulator partSim spring 32 33 $springks $springkd $strength
simulator partSim spring 33 34 $springks $springkd $strength
simulator partSim spring 34 35 $springks $springkd $strength
simulator partSim spring 35 36 $springks $springkd $strength
simulator partSim spring 36 37 $springks $springkd $strength
simulator partSim spring 37 38 $springks $springkd $strength
simulator partSim spring 38 39 $springks $springkd $strength
simulator partSim spring 39 40 $springks $springkd $strength
simulator partSim spring 40 41 $springks $springkd $strength
simulator partSim spring 41 42 $springks $springkd $strength
simulator partSim spring 42 43 $springks $springkd $strength
simulator partSim spring 43 44 $springks $springkd $strength
simulator partSim spring 44 45 $springks $springkd $strength
simulator partSim spring 45 46 $springks $springkd $strength
simulator partSim spring 46 47 $springks $springkd $strength
simulator partSim spring 47 48 $springks $springkd $strength
simulator partSim spring 48 49 $springks $springkd $strength
simulator partSim spring 49 50 $springks $springkd $strength
simulator partSim spring 50 51 $springks $springkd $strength
simulator partSim spring 51 52 $springks $springkd $strength
simulator partSim spring 52 53 $springks $springkd $strength
simulator partSim spring 53 54 $springks $springkd $strength
simulator partSim spring 54 55 $springks $springkd $strength
simulator partSim spring 55 56 $springks $springkd $strength
simulator partSim spring 56 57 $springks $springkd $strength

set strength 7
set springks2 70
simulator partSim spring 0 29 $springks2 $springkd $strength
simulator partSim spring 1 30 $springks2 $springkd $strength
simulator partSim spring 2 31 $springks2 $springkd $strength
simulator partSim spring 3 32 $springks2 $springkd $strength
simulator partSim spring 4 33 $springks2 $springkd $strength
simulator partSim spring 5 34 $springks2 $springkd $strength
simulator partSim spring 6 35 $springks2 $springkd $strength
simulator partSim spring 7 36 $springks2 $springkd $strength
simulator partSim spring 8 37 $springks2 $springkd $strength
simulator partSim spring 9 38 $springks2 $springkd $strength
simulator partSim spring 10 39 $springks2 $springkd $strength
simulator partSim spring 11 40 $springks2 $springkd $strength
simulator partSim spring 12 41 $springks2 $springkd $strength
simulator partSim spring 13 42 $springks2 $springkd $strength
simulator partSim spring 14 43 $springks2 $springkd $strength
simulator partSim spring 15 44 $springks2 $springkd $strength
simulator partSim spring 16 45 $springks2 $springkd $strength
simulator partSim spring 17 46 $springks2 $springkd $strength
simulator partSim spring 18 47 $springks2 $springkd $strength
simulator partSim spring 19 48 $springks2 $springkd $strength
simulator partSim spring 20 49 $springks2 $springkd $strength
simulator partSim spring 21 50 $springks2 $springkd $strength
simulator partSim spring 22 51 $springks2 $springkd $strength
simulator partSim spring 23 52 $springks2 $springkd $strength
simulator partSim spring 24 53 $springks2 $springkd $strength
simulator partSim spring 25 54 $springks2 $springkd $strength
simulator partSim spring 26 55 $springks2 $springkd $strength
simulator partSim spring 27 56 $springks2 $springkd $strength
simulator partSim spring 28 57 $springks2 $springkd $strength


simulator partSim integration symplectic .005
simulator partSim ground 5000 300
simulator partSim gravity -10.8
