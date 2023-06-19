
import ReducedChallenge
import Challenge

def main():
	Test_1="HELLO WORLD"
	Solution1=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', 'KD', 'AH', '2H', '3H', '4H', '5H', '6H', '7H', '8H', 'KH', '9S', '8S', '3S', '5S', '4S', 'QS', 'TH', '6S', 'QH', '2S', '9H', 'AS', '7S', 'JH', 'KS', 'TS', 'JS']
	Test_2=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '8D', 'KS', 'AH', 'QH', 'JH', 'TD', 'TS', 'KH', '7S', '9S', '6S', '9H', '2S', '7D', '7H', '6H', 'QD', '8S', '3H', 'KD', '5H', 'QS', 'TH', 'AS', '5S', 'JS', '2H', '4H', '3S', '4S', 'JD', '8H', '9D']
	Solution2="WAYNEWANTEDTHISTOBEHARDER"
	Test_3=" ATHROUGHZ "
	Solution3=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', 'KD', 'AH', '2H', '3H', '4H', '5H', '6H', '7H', '8H', '9H', 'TH', '8S', 'AS', '3S', '2S', 'KS', 'KH', '5S', 'QH', 'JS', 'TS', '7S', '6S', '4S', 'JH', '9S', 'QS']
	Test_4=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '6D', 'TD', 'JS', 'QS', 'TH', '8D', '8S', '6H', 'QH', 'AH', 'TS', 'KS', '5S', '9S', '9D', '5H', '5D', '9H', 'QD', 'KH', 'AS', '6S', '4S', '7H', '8H', '7S', '2S', '7D', 'KD', 'JH', '3H', '3S', 'JD', '2H', '4H']
	Solution4="TOWER PREPARING FOR TAKEOFF"
	Test_5="QWERTYUIOP"
	Solution5=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', 'KD', 'AH', '2H', '3H', '4H', '5H', '6H', '7H', '8H', '9H', '3S', '6S', 'QH', 'KH', 'QS', 'TS', 'KS', '9S', '7S', 'JH', 'TH', '4S', 'JS', '5S', 'AS', '8S', '2S']
	Test_6=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', 'KD', 'AH', '2H', '3H', '4H', '5H', '6H', '8H', '2S', 'JH', 'TS', 'QH', '8S', '7H', '4S', 'TH', '9H', '3S', 'KH', 'QS', 'JS', 'AS', '5S', '7S', 'KS', '6S', '9S']
	Solution6="ACE OF SPADES"
	Test_7="SPACE BETWEEN WORDS"
	Solution7=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', '2H', '9S', 'QH', 'TH', '5S', 'JH', '3S', '5H', '6H', 'KS', '3H', '7S', '4S', '4H', 'KH', 'TS', '6S', '8H', 'AS', 'KD', '9H', '8S', 'AH', 'QS', '7H', 'JS', '2S']
	Test_8=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', 'KD', 'AH', '2H', '3H', '4H', 'JS', 'JH', 'TH', 'AS', '4S', '6S', 'KS', '2S', '5H', '7H', '8H', '7S', 'QS', '9S', '6H', '3S', 'TS', 'QH', 'KH', '5S', '9H', '8S']
	Solution8="I HAVE A SECRET"
	Test_9=" "
	Solution9=['AC', '2C', '3C', '4C', '5C', '6C', '7C', '8C', '9C', 'TC', 'JC', 'QC', 'KC', 'AD', '2D', '3D', '4D', '5D', '6D', '7D', '8D', '9D', 'TD', 'JD', 'QD', 'KD', 'AH', '2H', '3H', '4H', '5H', '6H', '7H', '8H', '9H', 'TH', 'JH', 'QH', 'KH', 'AS', '2S', '3S', '4S', '5S', '6S', '7S', '8S', '9S', 'TS', 'JS', 'QS', 'KS']
	Test_10=['KC', '7C', '3C', 'TD', '2C', '9H', '4D', 'QS', '8H', 'AH', 'KH', '8S', 'TS', '4S', '2S', '5D', '9D', '4H', '5H', 'AC', '7S', 'JD', '5C', '2H', 'QC', 'TH', 'JS', '6S', '6C', '6D', 'QH', '6H', '9S', '3D', '5S', '7H', '2D', '8D', 'KD', 'AS', '4C', '3H', 'AD', 'JH', '8C', 'KS', 'JC', '9C', 'TC', '3S', '7D', 'QD']
	Solution10="A                                              A"

	x = 0
	for test, solution in [[Test_1, Solution1], [Test_2, Solution2], [Test_3, Solution3], [Test_4, Solution4], 
	 [Test_5, Solution5], [Test_6, Solution6], [Test_7, Solution7], [Test_8, Solution8], [Test_9, Solution9], [Test_10, Solution10]
	]:
		function = ReducedChallenge.decode if(isinstance(test, list)) else ReducedChallenge.encode
		function_inverse = ReducedChallenge.decode if(not isinstance(test, list)) else ReducedChallenge.encode
		print(f"—————————————— TEST {x} ——————————————")
		x+=1
		print(test)
		print(solution)
		print(function(test))
		print(function_inverse(function(test)))

		assert(function(test) == solution)

if(__name__ == "__main__"):
	main()
