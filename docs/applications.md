#General Context 

* Targets:
  - maple-mini
  - arduino (?)
  pour le pilotage de robot (ou de carte embarquée) dans un cadre éducatif
  
* Front-ends:
  - blockly
  - un langage textuel (pour passionné notamment) (?)...
     (interopérable) 

* Utilisateurs potentiels:
  - élèves : maternelle (?), primaire, collège, lycée, voire plus
  - passionnés ? DIY

#Exemple d'applications à programmer

* asservissement simple:
   
/* asservir le robot à la valeur du capteur de distance: */
constant_dist(x) {
  do (always) 
  {
    error = x - dist_sensor;
    set_speed (0.1* error);
    sleep(10);
  }
}

   dist_sensor et set_speed sont des primitives bas-niveau immédiates

   ;; asservir la roue d'un robot à une vitesse donnée
   
wheel_speed(w,x) {   
  do (always) {
    error = x - wheel_speed;
    set_power (w, 0.1 * error);
    sleep (10);
  }
}
  
wheel_speed et set_power sont des primitives bas-niveau

* faire faire un parcours au robot, un carré, etc. Avec des ordres d'avance/tourne de haut niveau.
  appliquer pour illustrer les concepts de forme géométrique, de polygone, d'angle, de côtés. 

parcours () {
  do 4 { // do it 4 times
    go_forward (10, 0.5); // go forward during 10 sec at speed 0.15 m/s
    turn (90, 10); // turn to the left of 90 deg at 10 deg/s
  }
}

* avancer en évitant les obstacles

sense_and_avoid () {
  do (always) {
    if (dist_sensor < 0.30) {
      set_speed(0.0);
      turn_on_led (0);
      turn (90, 10);
      turn_off_led (0);
    }
    set_speed(0.1);
  }
}

* chercher la direction avec la distance la plus grande pour avancer

best_direction () {
  max_dist := 0;
  max_dir := 0;
  current_dir := 0;
  do 36 {
    if (dist_sensor > max_dist) {
      max_dist := dist_sensor;
      max_dir := current_dir;
    }
    turn (10, 1);
    current_dir := current_dir + 10;
  }
  return max_dir;
}

* faire un scan des obstacles et le retourner à l'utilisateur sous forme de liste, et l'afficher graphiquement.

distance_scan () {
  graph := ();
  current_dir := 0;
  do 36 {
    graph := graph @ (current_dir dist_sensor);
    turn (10, 1);
    current_dir := current_dir + 10;
  }
  plot graph; // Affiche le plot dans l'interface
}
    
* faire jouer une spline unidimensionnelle à un servo-moteur

* faire jouer une spline mutidimensionnelle à une patte / robot.

* suivre une ligne pour le robot à roue.

* résoudre un labyrinthe avec le robot à roue + capteur infrarouge

* faire le tour de d'un objet (avec capteur de distance)

* "ranger" des objets sur une table.
  (avec des fonctions de haut niveau)

* quelles primitives pour un jeu de foot ?
