
// Version de la entidad Player del servidor
// Ver si tiene sentido conservarla o si se puede usar la misma
// O ver alguna alternativa de almacenar el estado del juego sin mantener
// una copia de las entidades en el server
class PlayerTestNet {
private:
  int x;
  int y;
  const int id;
public:
  PlayerTestNet(int id);

  ~PlayerTestNet();
};
