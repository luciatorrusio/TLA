def factorial(x):
	resp = 1
	i = 1
	while(int( i <= x )):
		resp = ( resp * i )
		i = ( i + 1 )

	i = 1
	return resp

def main():
	var = factorial(( 5 % 10 ))
	print("Resultado:", var)
	return 0

main()
