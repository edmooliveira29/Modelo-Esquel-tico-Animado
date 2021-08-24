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
    
%     for num_repet_filt = 1:numero_repeticoes_filtragem
% 
%         if num_repet_filt == 1
%             [sinal_filtrado, sinal_medio1] = filtro_media_nao_causal(angulo1,janela);
%         elseif num_repet_filt > 1
%             [sinal_filtrado, sinal_medio1] = filtro_media_nao_causal(angulo1_corrigido,janela);
%         end;
%         sinal_medio1_sem_media = sinal_medio1 - mean(sinal_medio1);
% 
%         fator = std(angulo1_sem_media(inc_inicial_calculo_std:end-decrem_final_calculo_std)) / std(sinal_medio1_sem_media(inc_inicial_calculo_std:end-decrem_final_calculo_std));
%         angulo1_corrigido = mean(sinal_medio1) + sinal_medio1_sem_media*fator;
%         
%     end
    Fs = 30; %frequência de amostragem (frame rate)
    N = 3; %ordem do filtro - valores 3 e 4
    freq_corte = 2.0; %frequência de corte do filtro passa-baixas - 0.5, 1.0 e 2.0(Hz)
    Wn = freq_corte / (Fs/2)
    [B,A] = butter(N,Wn);
    angulo1_filtrado_sem_media = filter(B,A,angulo1_sem_media);
    fator = std(angulo1_sem_media(inc_inicial_calculo_std:end-decrem_final_calculo_std)) / std(angulo1_filtrado_sem_media(inc_inicial_calculo_std:end-decrem_final_calculo_std));
    angulo1_corrigido = mean(angulo1) + angulo1_filtrado_sem_media*fator;
    
    angulos_processados = [angulos_processados; angulo1_corrigido];
    
end;

num_ang = 1;
angulo1 = angulos(num_ang,pontos_excluidos:end-pontos_excluidos,numero_individuo)*180/pi;
%plot(angulo1);
hold on;
plot(angulos_processados(num_ang,:),'g--');
% plot(angulos_processados(num_ang+3,:),'r--');

save angulos_processados.mat angulos_processados;

angles = load('angulos_processados.mat');
angle_1_person = angles.angulos_processados(:,:,1);

angle_1_person = transpose(angle_1_person);
angle_1_person_plot = transpose(angle_1_person(1:3593));
dlmwrite('angle_1_person.csv',angle_1_person, 'delimiter', ',', 'precision', 3) 