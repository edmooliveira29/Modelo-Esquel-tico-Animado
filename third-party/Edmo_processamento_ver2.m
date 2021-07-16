clear;
close all;
load angulos_SemMudancaCoordenadas.mat

numero_individuo = 1;
janela = 15;
pontos_excluidos = 30;
inc_inicial_calculo_std = 50;
decrem_final_calculo_std = 50;

numero_repeticoes_filtragem = 2;
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
%plot(angulo1);
hold on;
plot(angulos_processados(1,:),'black');
plot(angulos_processados(2,:),'blue');
plot(angulos_processados(3,:),'red');
save angulos_processados.mat angulos_processados;

angles = load('angulos_processados.mat');
angle_1_person = angles.angulos_processados(:,:,1);

angle_1_person = transpose(angle_1_person);
angle_1_person_plot = transpose(angle_1_person(1:3593));
dlmwrite('angle_1_person.csv',angle_1_person, 'delimiter', ',', 'precision', 3) 
