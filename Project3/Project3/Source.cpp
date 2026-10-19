int value;
while (true) {
	std::cout << prompt;
	if (std::cin >> value) {
		std::cin.ignore(std::numeric_limits<std::streamsixe>::max(), '\n');
		return value;
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsixe>::max(), '\n');
	std::cout << "Ошибка \n";

}

