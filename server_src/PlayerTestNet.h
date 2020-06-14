
// Version de la entidad Player del servidor
// Ver si tiene sentido o si se puede usar la misma que para el cliente
// O ver alguna alternativa de almacenar el estado del juego sin mantener
// una copia de las entidades en el server
class PlayerTestNet {
private:
  int x;
  int y;
  const int id;
public:
  explicit PlayerTestNet(int id);

  ~PlayerTestNet();

  const int getX();

  const int getY();

  void setX(int new_x);

  void setY(int new_y);
};
