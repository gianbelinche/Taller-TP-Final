#include "BankLocker.h"

#include <unordered_map>

class Bank {
private:
  std::unordered_map<int, BankLocker> lockers;
public:
  Bank();

  ~Bank();

  std::vector<Item*>& getUserItems(int id);

  void addGoldTo(int id);
};
