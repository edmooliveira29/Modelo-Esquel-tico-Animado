clear;
    % load marcha_ijk.mat;
    load marcha_SemMudancaCoordendas;
    for n_individuos = 1:20
        fprintf('%s %d \n\n',['Extraindo angulos do individuo:'],n_individuos);
        n_frames = size(marcha_ijk{n_individuos}.dados);
        for frames = 1:n_frames(end)

            Vd = marcha_ijk{n_individuos}.dados(1,:,frames) - marcha_ijk{n_individuos}.dados(2,:,frames);
            Vce = marcha_ijk{n_individuos}.dados(14,:,frames) - marcha_ijk{n_individuos}.dados(13,:,frames);
            Vpe = marcha_ijk{n_individuos}.dados(15,:,frames) - marcha_ijk{n_individuos}.dados(14,:,frames);
            Vpee = marcha_ijk{n_individuos}.dados(16,:,frames) - marcha_ijk{n_individuos}.dados(15,:,frames);
            Vcd = marcha_ijk{n_individuos}.dados(18,:,frames) - marcha_ijk{n_individuos}.dados(17,:,frames);
            Vpd = marcha_ijk{n_individuos}.dados(19,:,frames) - marcha_ijk{n_individuos}.dados(18,:,frames);
            Vped = marcha_ijk{n_individuos}.dados(20,:,frames) - marcha_ijk{n_individuos}.dados(19,:,frames);

            mod_Vd = sqrt(sum(Vd.^2));
            mod_Vce = sqrt(sum(Vce.^2));
            mod_Vpe = sqrt(sum(Vpe.^2));
            mod_Vpee = sqrt(sum(Vpee.^2));
            mod_Vcd = sqrt(sum(Vcd.^2));
            mod_Vpd = sqrt(sum(Vpd.^2));
            mod_Vped = sqrt(sum(Vped.^2));

    %         angulos(1,frames,n_individuos) = pi + acos(dot(Vd,Vce)/[mod_Vd*mod_Vce]);
            if Vce(2) <= 0
                angulos(1,frames,n_individuos) = pi + acos(dot(Vd,Vce)/[mod_Vd*mod_Vce]);
            elseif Vce(2) > 0
                angulos(1,frames,n_individuos) = pi - acos(dot(Vd,Vce)/[mod_Vd*mod_Vce]);
            end;
            angulos(2,frames,n_individuos) = pi - acos(dot(Vce,Vpe)/[mod_Vce*mod_Vpe]);
            angulos(3,frames,n_individuos) = pi + acos(dot(Vpe,Vpee)/[mod_Vpe*mod_Vpee]);

    %         angulos(4,frames,n_individuos) = pi + acos(dot(Vd,Vcd)/[mod_Vd*mod_Vcd]);
            if Vcd(2) <= 0
                angulos(4,frames,n_individuos) = pi + acos(dot(Vd,Vcd)/[mod_Vd*mod_Vcd]);
            elseif Vcd(2) > 0
                angulos(4,frames,n_individuos) = pi - acos(dot(Vd,Vcd)/[mod_Vd*mod_Vcd]);
            end;
            angulos(5,frames,n_individuos) = pi - acos(dot(Vcd,Vpd)/[mod_Vcd*mod_Vpd]);
            angulos(6,frames,n_individuos) = pi + acos(dot(Vpd,Vped)/[mod_Vpd*mod_Vped]);        
        end;
    end;
    file = save angulos_SemMudancaCoordenadas.mat angulos;
    % save angulos.mat angulos;
