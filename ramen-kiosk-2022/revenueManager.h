#pragma once
class RevenueManager
{
	private:
		unsigned int today;

	public:
		RevenueManager(void);

		void Calculate(unsigned int amount);

		const unsigned int& Today = today;
};

