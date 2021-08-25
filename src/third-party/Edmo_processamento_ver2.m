clear;
close all;
load angulos_SemMudancaCoordenadas.mat

numero_individuo = 1;
janela = 15;
pontos_excluidos = 30;
inc_inicial_calculo_std = 50;
decrem_final_calculo_std = 50;

numero_repeticoes_filtragem = 3;
numero_de_angulos = 6;
angulos_processados = []; 

for num_ang = 1:numero_de_angulos
    
    %Tratamento do angulo 1
    angulo1 = angulos(num_ang,pontos_excluidos:end-pontos_excluidos,numero_individuo)*180/pi;
    angulo1_sem_media = angulo1 - mean(angulo1);  
    
    for num_repet_filt = 1:numero_repeticoes_filtragem

        if num_repet_filt == 1
            [sinal_filtrado, sinal_medio1] = filtro_media_nao_causal(angulo1,janela);
        elseif num_repet_filt > 1
            [sinal_filtrado, sinal_medio1] = filtro_media_nao_causal(angulo1_corrigido,janela);
        end;
        sinal_medio1_sem_media = sinal_medio1 - mean(sinal_medio1);

        fator = std(angulo1_sem_media(inc_inicial_calculo_std:end-decrem_final_calculo_std)) / std(sinal_medio1_sem_media(inc_inicial_calculo_std:end-decrem_final_calculo_std));
        angulo1_corrigido = mean(sinal_medio1) + sinal_medio1_sem_media*fator;
        
    end
    
    angulos_processados = [angulos_processados; angulo1_corrigido];
    
end;
num_ang = 1;
angulo1 = angulos(num_ang,pontos_excluidos:end-pontos_excluidos,numero_individuo)*180/pi;
hold on;
title ('Ângulos x frames')
xlabel ('frames - fps');
ylabel ('ângulos °');
% plot(angulo1, 'blue');
plot(angulos_processados(1,:),'black');
% plot(angulos_processados(2,:),'blue');
%  plot(angulos_processados(3,:),'red');
% plot(angulos_processados(4,:),'yellow');
% plot(angulos_processados(5,:),'green');
%  plot(angulos_processados(6,:),'cyan');


angulos_sintetizados = repmat(angulos_processados(:,1048:1096),1,30);
% plot(angulos_sintetizados(1,:),'red');
% plot(angulos_sintetizados(2,:),'blue');
% plot(angulos_sintetizados(3,:),'red');
% plot(angulos_sintetizados(4,:),'yellow');
% plot(angulos_sintetizados(5,:),'green');
% plot(angulos_sintetizados(6,:),'black');


%  save angulos_processados.mat angulos_processados;
 save angulos_sintetizados.mat angulos_sintetizados;

angles = load('angulos_sintetizados.mat');
angle_1_person = angles.angulos_sintetizados(:,:,1);

angle_1_person = transpose(angle_1_person);
angle_1_person_plot = transpose(angle_1_person(1:3593));
dlmwrite('angle_1_person.csv',angle_1_person, 'delimiter', ',', 'precision', 3) 
