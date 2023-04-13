  // X Check

  logic is_access_phase;
  assign is_access_phase = apb_psel_i && apb_penable_i;

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    is_access_phase |-> !$isunknown( apb_pready_o )
  ) else begin
    $error( "pready_o isunknown when access_phase" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    apb_psel_i |-> !$isunknown( apb_penable_i )
  ) else begin 
    $error( "penable_i isunknown when psel_i" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    !$isunknown( rstn_i )
  ) else begin 
    $error( "presetn_i isunknown" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    !$isunknown( clk_i )
  ) else begin
    $error( "clk_i isunknown" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    !$isunknown( apb_psel_i )
  ) else begin
    $error( "psel_i isunknown" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    is_access_phase |-> !$isunknown( apb_pwrite_i )
  ) else begin
    $error( "pwrite_i isunknown when access_phase" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    ( is_access_phase && apb_pwrite_i ) |-> !$isunknown( apb_pwdata_i )
  ) else begin
      $error( "pwdata_i isunknown when access_phase && pwrite_i" );
      $fatal;
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    ( is_access_phase && apb_pready_o && ~apb_pwrite_i ) |-> !$isunknown( apb_prdata_o )
  ) else begin
    $error( "prdata_o isunknown when access_phase && pready_o && ~pwrite_i" );
    $fatal;
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    ( is_access_phase && apb_pready_o ) |-> !$isunknown( apb_pslverr_o )
  ) else begin
    $error( "pslverr_o isunknown when access_phase && pready_o" );
    $fatal;
  end

  // Behavioral

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    $rose( apb_psel_i ) |-> ##1 apb_penable_i && !$past( apb_penable_i )
  ) else begin
    $fatal( "penable_i after psel_i error" );
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    apb_pready_o && is_access_phase |-> ##1 $fell( apb_penable_i )
  ) else begin
    $fatal( "penable_i after pready didn't fall" );
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    $rose( apb_penable_i ) && apb_psel_i |-> ##1 ( $stable( apb_penable_i ) && $stable( apb_paddr_i ) && $stable( apb_pwrite_i ) && $stable( apb_psel_i ) )  throughout ( apb_pready_o[->1] )
  ) else begin
    $fatal( "during access phase unstable signals" );
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    $rose(apb_pready_o) |-> ##1 $fell(apb_pready_o)
  ) else begin
    $fatal( "pready lasts longer than 1 clock cycle" );
  end

  assert property ( @(posedge clk_i) 
    disable iff( ~rstn_i )
    apb_pslverr_o |-> apb_pready_o
  ) else begin
    $fatal( "pslverr_o when pready_o == 0" );
  end
