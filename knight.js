class KNIGHT {
  constructor(row, col) {
    // Location
    this.row = row;
    this.col = col;
    //if this node cheked 
    this.cheked = false;

    // how many moves we did from the begining
    this.g = 0;


    // nodes where is possible to move 
    this.moves = [];


    // Where did I come from?
    this.previous = undefined;

    this.show = function() {
      console.log(`(${this.row} , ${this.col} == stips :${this.g} )`)
    }
    // Figure out where I can move
    this.nextMove = function () {

      if (col < 6) {
        if (row < 7) {
          // 1 down -- 2 rigth
          this.moves.push(grid[row + 1][col + 2]);
        }
        if (row > 0) {
          // 1 up -- 2 right
          this.moves.push(grid[row - 1][col + 2]);
        }
      }

      if (col < 7) {
        if (row < 6) {
          // 2 down -- 1 right
          this.moves.push(grid[row + 2][col + 1]);
        }
        if (row > 1) {
          // 2 up -- 1 right
          this.moves.push(grid[row - 2][col + 1]);
        }
      }

      if (col > 0) {
        if (row > 1) {
          this.moves.push(grid[row - 2][col - 1]);
        }
        if (row < 6) {
          this.moves.push(grid[row + 2][col - 1]);
        }
      }

      if (col > 1) {
        if (row > 0) {
          this.moves.push(grid[row - 1][col - 2]);
        }
        if (row < 7) {
          this.moves.push(grid[row + 1][col - 2]);
        }
      }

    };
  }
}

//===================================setup the grid ======================
let grid = new Array(8);
for (let i = 0; i < 8; i++) {
  grid[i] = new Array(8);
}

for (let i = 0; i < 8; i++) {
  for (let j = 0; j < 8; j++) {
    grid[i][j] = new KNIGHT(i,j);
  }
}

// decode the position given ======================================================

function decode(str) {
  const alpha = ['a','b','c','d','e','f','g','h'];
  let arr = str.split('');
  let row = 8 - parseInt(arr[1]);
  let col = alpha.findIndex( e => arr[0] == e);

  return grid[row][col];
}


// ======= main function=============================================================

function knight(start, finish) {
  let queue = [];
  let begin = decode(start);
  let end = decode(finish);

  
  queue.push(begin);
  while (queue.length != 0) {
    // evaluate nodes they still in queue
    let current = queue.shift();
    // if this queue is end return
    if (current === end) {
      // print path from the end to begining

      // let tmp = current;
      // while (tmp.previous != undefined) {
      //   tmp.show();
      //   tmp = tmp.previous;
      // }

      // return how many stips we did 
      break;

    }
    current.cheked = true ; // set this node as cheked

    // get its next moves 
    current.nextMove();
    // if they arn't in the queue already--add them  
    // or if we didn't check them too
    for (let index = 0; index < current.moves.length; index++) {

      let  move = current.moves[index];
      if (!queue.includes(move) && !move.cheked) {
        move.previous = current;
        move.g = current.g + 1;
        queue.push(move);
        //move.show();
      }
    }

  }
  return end.g;
}


console.log(knight("a1","f7"));