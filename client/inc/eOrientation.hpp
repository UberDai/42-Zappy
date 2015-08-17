//               .-'''''-.
//             .'         `.
//            :             :        File       : eOrientation.hpp
//           :               :       Creation   : 2015-06-08 23:24:53
//           :      _/|      :       Last Edit  : 2015-06-09 00:57:07
//            :   =/_/      :        Author     : nsierra-
//             `._/ |     .'         Mail       : nsierra-@student.42.fr
//          (   /  ,|...-'
//           \_/^\/||__
//        _/~  `""~`"` \_
//     __/  -'/  `-._ `\_\__
//   /jgs     /-'`  `\   \  \-

#ifndef EORIENTATION_HPP
# define EORIENTATION_HPP

enum eOrientation : int {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

#endif /* EORIENTATION_HPP */

// posX, posY

// Y = 0

// Y = mapping.second != 0 ? Y * mapping.second : Y
// X = mapping.first != 0 ? X * mapping.first : X

// while (Y <= LEVEL)
// {
// 	X = -Y;
// 	while (X <= Y)
// 	{
// 		print(posX + X, posY + Y)
// 		X++;
// 	}
// 	println
// 	Y++;
// }
