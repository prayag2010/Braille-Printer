//37 characters, 26 alpahbets + 10 numbers + 1 blank space
//array mapping - [w][x][y] - w = total arrays, x = rows, y = columns

//starting with 5 characters
boolean character_map[37][3][2] =
{
	{	//a
		{true, false},
		{false, false},
		{false, false}
	},
	{	//b
		{true, false},
		{true, false},
		{false, false}
	},
	{	//c
		{true, true},
		{false, false},
		{false, false}
	},
	{	//d
		{true, true},
		{false, true},
		{false, false}
	},
	{	//e
		{true, false},
		{false, true},
		{false, false}
	},
	{	//f
		{true, true},
		{true, false},
		{false, false}
	},
	{	//g
		{true, true},
		{true, true},
		{false, false}
	},
	{	//h
		{true, false},
		{true, true},
		{false, false}
	},
	{	//i
		{false, true},
		{true, false},
		{false, false}
	},
	{	//j
		{false, true},
		{true, true},
		{false, false}
	},
	{	//k
		{true, false},
		{false, false},
		{true, false}
	},
	{	//l
		{true, false},
		{true, false},
		{true, false}
	},
	{	//m
		{true, true},
		{false, false},
		{true, false}
	},
	{	//n
		{true, true},
		{false, true},
		{true, false}
	},
	{	//o
		{true, false},
		{false, true},
		{true, false}
	},
	{	//p
		{true, true},
		{true, false},
		{true, false}
	},
	{	//q
		{true, true},
		{true, true},
		{true, false}
	},
	{	//r
		{true, false},
		{true, true},
		{true, false}
	},
	{	//s
		{false, true},
		{true, false},
		{true, false}
	},
	{	//t
		{false, true},
		{true, true},
		{true, false}
	},
	{	//u
		{true, false},
		{false, false},
		{true, true}
	},
	{	//v
		{true, false},
		{true, false},
		{true, true}
	},
	{	//w
		{false, true},
		{true, true},
		{false, true}
	},
	{	//x
		{true, true},
		{false, false},
		{true, true}
	},
	{	//y
		{true, true},
		{false, true},
		{true, true}
	},
	{	//z
		{true, false},
		{false, true},
		{true, true}
	},
	{	//' '
		{false, false},
		{false, false},
		{false, false}
	},
};