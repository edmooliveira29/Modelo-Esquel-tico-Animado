%angles = load('angulos_sem_mudancas_de_coordenadas.mat');
angles = load('angulos_processados.mat');

%angle_1_person = angles.angulos(:,:,1);
angle_1_person = angles.angulos_processados(:,:,1);

angle_1_person = transpose(angle_1_person);
angle_1_person_plot = transpose(angle_1_person(1:3593));
plot(angle_1_person_plot);
dlmwrite('angle_1_person.csv',angle_1_person, 'delimiter', ',', 'precision', 3) 

march = load('marcha_sem_mudancas_de_coordenadas.mat','-ASCII');
march_1_person = march(:,:,1);
march_1_person = transpose(march_1_person);

dlmwrite('march_1_person.csv',march_1_person, 'delimiter', ',','precision', 3);
