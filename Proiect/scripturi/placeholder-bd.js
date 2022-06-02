var listaReviews = [];

function updateListaReviews(){//ne imaginam ca raspunsul vine de la un server
    listaReviews = [
        new Review(0, 0, "Donkey Kong","Donkey Kong is a video game series created by Shigeru Miyamoto. It follows the adventures of an ape named Donkey Kong and his clan of other apes and monkeys. The franchise consists of platform games, originally single-screen action puzzle games, and later side-scrolling platformers."),
        new Review(0, 1, "Pac Man","Pac-Man is an action maze chase video game; the player controls the eponymous character through an enclosed maze. The objective of the game is to eat all of the dots placed in the maze while avoiding four colored ghosts — Blinky, Pinky, Inky, and Clyde — that pursue him."),
        new Review(0, 2, "Super Mario Bros","Super Mario Bros. is a platform game. In the game, Mario must race through the Mushroom Kingdom and save Princess Toadstool (later Princess Peach) from Bowser. Mario jumps, runs, and walks across each level. The worlds are full of enemies and platforms, and open holes."),
        new Review(0, 3, "Star Wars 1983","Star Wars is a first-person rail shooter video game designed by Mike Hally and released in arcades in 1983 by Atari, Inc. It uses 3D color vector graphics to simulate the assault on the Death Star from the 1977 film Star Wars."),
        new Review(0, 4, "The Legend of Zelda", "Follows the story of a young boy named Link that must save a kidnapped princess from the evil, demonic Ganon, who put a spell on his lair which can only be removed with the 3 pieces of the Triforce, a golden triangle with mystical powers.")
    ]
}

function obtinereVersiuneSite(){//ne imaginam ca raspunsul vine de la un server
    return "1.5b";
}

function incarcare(){//raspunsul vine de la un server lorem ipsum
    if(listaReviews.length < 195){//pe server sunt 200 review-uri
        let animatieLoading = document.getElementsByClassName("imagine-loading")[0];
        if(animatieLoading != null){
            animatieLoading.setAttribute("id", "");
            animatie_on = true;
        }
        for(let i = 0; i < 5; i++){
            //puteam folosi un xmlhttprequest in loc de jquery, dar e mai simplu asa
            $.get("https://jsonplaceholder.typicode.com/comments/" + (listaReviews.length + i),function(data){
                listaReviews.push(new Review(parseInt(obtineCodImagineInaltime(listaReviews.length + 1)), obtineCodImagineLatime(listaReviews.length + 1), formatareTitlu(data), formatareDescriere(data)));
                randareReview(listaReviews.length - 1);
                updateLocalStorage(obtinereVersiuneSite());
                animatieLoading.setAttribute("id", "div-colapsat");
                animatie_on = false;
            });
        }
    }
}